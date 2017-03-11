# Install script for directory: /home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical

# Set the install prefix
IF(NOT DEFINED CMAKE_INSTALL_PREFIX)
  SET(CMAKE_INSTALL_PREFIX "/usr/local")
ENDIF(NOT DEFINED CMAKE_INSTALL_PREFIX)
STRING(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
IF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  IF(BUILD_TYPE)
    STRING(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  ELSE(BUILD_TYPE)
    SET(CMAKE_INSTALL_CONFIG_NAME "Release")
  ENDIF(BUILD_TYPE)
  MESSAGE(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
ENDIF(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)

# Set the component getting installed.
IF(NOT CMAKE_INSTALL_COMPONENT)
  IF(COMPONENT)
    MESSAGE(STATUS "Install component: \"${COMPONENT}\"")
    SET(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  ELSE(COMPONENT)
    SET(CMAKE_INSTALL_COMPONENT)
  ENDIF(COMPONENT)
ENDIF(NOT CMAKE_INSTALL_COMPONENT)

# Install shared libraries without execute permission?
IF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  SET(CMAKE_INSTALL_SO_NO_EXE "1")
ENDIF(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)

IF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/g2o/apps/g2o_hierarchical/simple_star_ops.h;/usr/local/include/g2o/apps/g2o_hierarchical/edge_creator.h;/usr/local/include/g2o/apps/g2o_hierarchical/edge_labeler.h;/usr/local/include/g2o/apps/g2o_hierarchical/backbone_tree_action.h;/usr/local/include/g2o/apps/g2o_hierarchical/edge_types_cost_function.h;/usr/local/include/g2o/apps/g2o_hierarchical/g2o_hierarchical_api.h;/usr/local/include/g2o/apps/g2o_hierarchical/star.h")
  IF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
  IF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  ENDIF (CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
FILE(INSTALL DESTINATION "/usr/local/include/g2o/apps/g2o_hierarchical" TYPE FILE FILES
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/simple_star_ops.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/edge_creator.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/edge_labeler.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/backbone_tree_action.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/edge_types_cost_function.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/g2o_hierarchical_api.h"
    "/home/xiarui/catkin_ws/src/Navigation_using_Octomap/g2o_with_orbslam2/g2o/apps/g2o_hierarchical/star.h"
    )
ENDIF(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")

