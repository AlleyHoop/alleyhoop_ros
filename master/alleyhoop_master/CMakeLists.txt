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
  LIBRARIES alleyhoop_master
  CATKIN_DEPENDS roscpp rospy tf
  # DEPENDS system_lib
)

include_directories(include
   ${catkin_INCLUDE_DIRS}
)

add_library(alleyhoop_master src/alleyhoop_controller.cpp
                             src/alleyhoop_vehicle.cpp
                             src/alleyhoop_feature_finder.cpp
)
target_link_libraries(alleyhoop_master 
   ${catkin_LIBRARIES}
)

add_executable(alleyhoop_core src/core.cpp)
target_link_libraries(alleyhoop_core alleyhoop_master 
   ${catkin_LIBRARIES}
)

install(DIRECTORY include/ DESTINATION include)

install(TARGETS
   alleyhoop_core
   alleyhoop_master
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
