cmake_minimum_required(VERSION 2.8.3)
project(alleyhoop_master)

add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
)

catkin_package(
  INCLUDE_DIRS include
  LIBRARIES alleyhoop_ros 
  CATKIN_DEPENDS roscpp rospy tf
  # DEPENDS system_lib
)

include_directories(include
   ${catkin_INCLUDE_DIRS}
)

add_library(alleyhoop_ros src/alleyhoop_controller.cpp
                             src/alleyhoop_vehicle.cpp
                             src/alleyhoop_feature_finder.cpp
)
target_link_libraries(alleyhoop_ros 
   ${catkin_LIBRARIES}
)

add_executable(alleyhoop_ros_node src/core.cpp)
target_link_libraries(alleyhoop_ros_node alleyhoop_ros 
   ${catkin_LIBRARIES}
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS
   alleyhoop_ros_node
   alleyhoop_ros
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
