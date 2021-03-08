cmake_minimum_required(VERSION 2.8.3)
project(td_ros)
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)
## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
#        object_msgs
        roscpp
        rospy
        std_msgs
        moveit_core
        moveit_visual_tools
        moveit_ros_planning
        moveit_ros_planning_interface
        tf
        gazebo_ros
        rosbag
#        eigen_conversions
#        tf
        )

set(GeoGraphic_LIBRARIES "")
#set(Glog_LIBRARIES "")

#include(cmake/YAML.cmake)
include(cmake/geographic.cmake)
#include(cmake/eigen.cmake)
#include(cmake/glog.cmake)
################################################
## Declare ROS dynamic reconfigure parameters ##
################################################

## To declare and build dynamic reconfigure parameters within this
## package, follow these steps:
## * In the file package.xml:
##   * add a build_depend and a run_depend tag for "dynamic_reconfigure"
## * In this file (CMakeLists.txt):
##   * add "dynamic_reconfigure" to
##     find_package(catkin REQUIRED COMPONENTS ...)
##   * uncomment the "generate_dynamic_reconfigure_options" section below
##     and list every .cfg file to be processed

## Generate dynamic reconfigure parameters in the 'cfg' folder
# generate_dynamic_reconfigure_options(
#   cfg/DynReconf1.cfg
#   cfg/DynReconf2.cfg
# )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
        INCLUDE_DIRS include
        LIBRARIES td_ros
        CATKIN_DEPENDS roscpp rospy std_msgs tf
        moveit_core
        moveit_visual_tools
        moveit_ros_planning
        moveit_ros_planning_interface
        gazebo_ros
        rosbag
        #  DEPENDS system_lib
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# add Eigen header files
include_directories( "/usr/local/include/eigen3" )
#template sophus
include_directories("/home/td/slam/install/sophus/include")
include_directories(
        include
        ${catkin_INCLUDE_DIRS}
        ${GAZEBO_INCLUDE_DIRS}
)


## Declare a C++ library
file(GLOB TFListener src/tf_listener/*.cpp)
file(GLOB Publisher src/publisher/*.cpp)
file(GLOB Subscriber src/subscriber/*.cpp)
file(GLOB SensorData src/sensor_data/*.cpp)
file(GLOB BagLib src/bag/*.cpp)

add_library(td_ros
        src/tool.cpp
        src/arm_moveit.cpp
        ${TFListener}
        ${Publisher}
        ${Subscriber}
        ${SensorData}
        ${BagLib}
        )
## Add cmake target dependencies of the library
## as an example, code may need to be generated before libraries
## either from message generation or dynamic reconfigure
add_dependencies(td_ros ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Declare a C++ executable
#add_executable(object_tf_broadcaster_node src/object_tf_broadcaster_node.cpp)
#add_executable(register_object_client src/register_object_client.cpp)

## Add cmake target dependencies of the executable
## same as for the library above
#add_dependencies(object_tf_broadcaster_node ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
#add_dependencies(register_object_client ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})

## Specify libraries to link a library or executable target against
target_link_libraries(td_ros PRIVATE
        ${catkin_LIBRARIES}
        ${GAZEBO_LIBRARIES}
        ${GeoGraphic_LIBRARIES}
#        ${Glog_LIBRARIES}
        )
#target_link_libraries(object_tf_broadcaster_node
#        td_ros
#        ${catkin_LIBRARIES}
#        )
#target_link_libraries(register_object_client
#        ${catkin_LIBRARIES}
#        )

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

## Mark executables and/or libraries for installation
#install(TARGETS td_ros
#        ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#        LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#        RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
#        )
#
### Mark cpp header files for installation
#install(DIRECTORY include/${PROJECT_NAME}/
#        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#        FILES_MATCHING PATTERN "*.h"
#
#        )
#install(DIRECTORY include/${PROJECT_NAME}/
#        DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#        FILES_MATCHING PATTERN "*.hpp"
#
#        )
#
#install(DIRECTORY launch/
#        DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
#        FILES_MATCHING PATTERN "*.launch"
#        )

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
# catkin_add_gtest(${PROJECT_NAME}-test test/test_td_ros.cpp)
# if(TARGET ${PROJECT_NAME}-test)
#   target_link_libraries(${PROJECT_NAME}-test ${PROJECT_NAME})
# endif()

## Add folders to be run by python nosetests
# catkin_add_nosetests(test)