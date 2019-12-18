cmake_minimum_required(VERSION 2.8.3)
project(alleyhoop_master)

add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  cv_bridge
  rospy
  tf
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES alleyhoop_ros alleyhoop_ros_sensors
  CATKIN_DEPENDS roscpp rospy tf
  # DEPENDS system_lib
)

include_directories(include
   ${catkin_INCLUDE_DIRS}
   ${OpenCV_INCLUDE_DIRS}
)

add_library(alleyhoop_ros  src/alleyhoop_ros_controller.cpp
                           src/alleyhoop_ros_vehicle.cpp
                           src/alleyhoop_ros_feature_finder.cpp
)
target_link_libraries(alleyhoop_ros 
   ${catkin_LIBRARIES}
)

add_library(alleyhoop_ros_sensors src/alleyhoop_ros_ultrasoon.cpp
                                  src/alleyhoop_ros_mono_camera.cpp
                                  src/alleyhoop_ros_lidar.cpp
)
target_link_libraries(alleyhoop_ros_sensors 
   ${catkin_LIBRARIES}
   ${OpenCV_LIBS}
)

add_library(alleyhoop_ros_actuators src/alleyhoop_ros_led.cpp)
target_link_libraries(alleyhoop_ros_actuators 
   ${catkin_LIBRARIES}
)

add_executable(alleyhoop_ros_node src/alleyhoop_ros_core.cpp)
target_link_libraries(alleyhoop_ros_node alleyhoop_ros alleyhoop_ros_sensors alleyhoop_ros_actuators
   ${catkin_LIBRARIES}
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS
   alleyhoop_ros_node
   alleyhoop_ros
   alleyhoop_ros_sensors
   alleyhoop_ros_actuators
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
