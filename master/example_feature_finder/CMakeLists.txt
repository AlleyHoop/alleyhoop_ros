cmake_minimum_required(VERSION 2.8.3)
project(example_feature_finder)

add_compile_options(-std=c++11)

find_package(OpenCV REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  alleyhoop_ros_msgs
  cv_bridge
  rospy
  tf
)

catkin_package(
  INCLUDE_DIRS include
  # LIBRARIES 
  CATKIN_DEPENDS roscpp rospy tf
  # DEPENDS system_lib
)

include_directories(include
   ${catkin_INCLUDE_DIRS}
   ${OpenCV_INCLUDE_DIRS}
)

add_executable(example_feature_finder src/feature_finder_server.cpp)
target_link_libraries(example_feature_finder
   ${catkin_LIBRARIES}
   ${OpenCV_LIBS}
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS
   example_feature_finder
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
