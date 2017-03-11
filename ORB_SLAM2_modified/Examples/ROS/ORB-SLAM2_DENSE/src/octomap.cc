#include<iostream>
#include<algorithm>
#include<fstream>
#include<chrono>

#include<ros/ros.h>
#include <cv_bridge/cv_bridge.h>

#include <pcl/common/transforms.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/statistical_outlier_removal.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/io/pcd_io.h>
#include <pcl_ros/transforms.h>
#include <pcl_conversions/pcl_conversions.h>
#include <pcl/point_cloud.h>


#include<opencv2/core/core.hpp>
#include <octomap/octomap.h>
#include <octomap_ros/conversions.h>
#include <octomap_msgs/conversions.h>
#include <octomap_msgs/Octomap.h>


#include <visualization_msgs/MarkerArray.h>
#include <visualization_msgs/Marker.h>
#include <geometry_msgs/Pose.h>

#include"../ORB_SLAM2_modified/include/System.h"
#include"../ORB_SLAM2_modified/include/pointcloudmapping.h"

#include <std_msgs/ColorRGBA.h>

octomap::OcTree tree( 0.01 );

pcl::PointCloud<pcl::PointXYZRGBA> pcl_cloud;
typedef octomap::point3d point3d;
ros::Publisher octomap_pub;
ros::Publisher map_pub;
unsigned int a =0,b=0; 

tf::TransformListener *tf_listener; 
point3d kinect_orig;

void publishMapAsMarkers(octomap::OcTree& octree); 

std_msgs::ColorRGBA getColorByHeight(double h) 
{
		double range = 2.05;
		h = 1.0 - std::min(std::max(h/range, 0.0), 1.0);
		h *= 0.8;
		std_msgs::ColorRGBA color;
		color.a = 1.0;
		// blend over HSV-values (more colors)

		double s = 1.0;
		double v = 1.0;

		h -= floor(h);
		h *= 6;
		int i;
		double m, n, f;

		i = floor(h);
		f = h - i;
		if (!(i & 1))
		f = 1 - f; // if i is even
		m = v * (1 - s);
		n = v * (1 - s * f);

		switch (i) 
		{
			case 6:
			case 0:
			color.r = v; color.g = n; color.b = m;
			break;
			case 1:
			color.r = n; color.g = v; color.b = m;
			break;
			case 2:
			color.r = m; color.g = v; color.b = n;
			break;
			case 3:
			color.r = m; color.g = n; color.b = v;
			break;
			case 4:
			color.r = n; color.g = m; color.b = v;
			break;
			case 5:
			color.r = v; color.g = m; color.b = n;
			break;
			default:
			color.r = 1; color.g = 0.5; color.b = 0.5;
			break;
		}

	return color;
}

static void pcl_callback(const sensor_msgs::PointCloud2& input)
{
// 	pcl::PointCloud<pcl::PointXYZI> tmp;
// 	pcl::fromROSMsg(input, tmp);
	tf::StampedTransform transform;
	octomap::Pointcloud octo_cloud;
	octomap::pointCloud2ToOctomap(input, octo_cloud);
	
	try
	{
		tf_listener->lookupTransform("/map", "/odom", ros::Time(0), transform);
		kinect_orig = point3d(transform.getOrigin().x(), transform.getOrigin().y(), -transform.getOrigin().z());
	}
	catch (tf::TransformException &ex) 
	{
		ROS_ERROR("%s",ex.what());
		ros::Duration(1.0).sleep();
    }

	tree.insertPointCloud(octo_cloud, kinect_orig);
	tree.updateInnerOccupancy();
	
/*	octomap_msgs::Octomap octo_msg;
	octomap_msgs::binaryMapToMsg(tree, octo_msg);
	octo_msg.header.frame_id = "/octomap";		msg.markers[i].ns = "map";
	octo_msg.header.stamp = ros::Time::now();*/	
//	octomap_pub.publish(octo_msg);
	publishMapAsMarkers(tree);
	
}

int main(int argc, char **argv)
{	
    ros::init(argc, argv, "orb_octomap");
    
	octomap::Pointcloud octo_cloud;
	tf_listener = new tf::TransformListener();
    ros::NodeHandle nh;
	ros::Subscriber receive = nh.subscribe("/pclPoint_out", 10, pcl_callback);
//     octomap_pub = nh.advertise<octomap_msgs::Octomap>("/octomap_out",100000); // here the number is the buffer
	map_pub = nh.advertise<visualization_msgs::MarkerArray>("/map_vis", 10);
	
//     ros::Rate loop_rate(50);
	
//     while(ros::ok())
//     {
// 		
// 		
//         ros::spinOnce();
//         loop_rate.sleep();
//     }
	ros::spin();
	tree.write("test.ot");
    return 0;
}

void publishMapAsMarkers(octomap::OcTree& octree) 
{
	visualization_msgs::MarkerArray msg;
	msg.markers.resize(octree.getTreeDepth()+1);

	typedef octomap::OcTree::iterator it_t;
	it_t it = octree.begin();
	it_t end = octree.end();
	// For leaf in leaves
	for (; it != end; ++it) 
	{
	// If occupied
		if (octree.isNodeOccupied(*it)) 
		{
			// Get some info about the leaf
			double x = it.getX();
			double y = it.getY();
			double z = it.getZ();
//			if (z > 0.1 && z < 2.0) 
//			{
				size_t depth = it.getDepth();
				// Insert a point for the leaf's cube
				geometry_msgs::Point leaf_origin;
				leaf_origin.x = x;
				leaf_origin.y = y;
				leaf_origin.z = z;
				msg.markers[depth].points.push_back(leaf_origin);
				// Determine and set the leaf's color by height
				msg.markers[depth].colors.push_back(getColorByHeight(leaf_origin.z));
//			}
			a++;
		}
	}
  // Finish the marker array setup
	std_msgs::ColorRGBA color;
	color.a = 1.0;
	for (size_t i = 0; i < msg.markers.size(); ++i) 
	{
		double size = octree.getNodeSize(i);

		msg.markers[i].header.frame_id = "/map";
		msg.markers[i].header.stamp = ros::Time::now();
		msg.markers[i].ns = "map";
		msg.markers[i].id = i;
		msg.markers[i].type = visualization_msgs::Marker::CUBE_LIST;
		msg.markers[i].scale.x = size;
		msg.markers[i].scale.y = size;
		msg.markers[i].scale.z = size;
		msg.markers[i].action = visualization_msgs::Marker::ADD;
		msg.markers[i].color = color;
		b++;
	}
  // Publish the marker array
	map_pub.publish(msg);
// 	ROS_INFO("The size of msg:%d", a);
// 	ROS_INFO("The size of tree:%d", b);
	
}
