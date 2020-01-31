cmake_minimum_required(VERSION 2.8.3)
project(raspi_ros_slave)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES raspi_ros_slave
#  CATKIN_DEPENDS roscpp rospy tf
#  DEPENDS system_lib
)

include_directories(
# include
  ${catkin_INCLUDE_DIRS}
)
