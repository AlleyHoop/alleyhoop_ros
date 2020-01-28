# AlleyHoop

An Urban innovations project. Development of an autonomous vehicle for haaglanden area.

Uses ROS for communication between components. The architecture is based on MVC design pattern. The core of the program can be found in the master source code. 
  * developed for ROS kinetic kame
  * the code is split in mainly three components. 
  * all the components where tested on variants of Ubuntu 16.04 armhf

  1. monitor
     * source code for monitoring the master
     * scripts for running nodes
     * scripts for setting up the monitor, from SD card itself to setting up ROS environment

  2. master
     * source code for controlling the autonomous car
     * scripts for running nodes
     * scripts for setting up the master, from SD card itself to setting up ROS environment
     * has a generated code API included
        - download and open index.html
     * dependent on the following packages
        - alleyhoop_ros_master
          * roscpp
          * sensor_msgs
          * std_msgs
          * alleyhoop_ros_msgs
          * cv_bridge
          * rospy
          * tf
        - alleyhoop_ros_msgs
          * sensor_msgs
          * std_msgs
        - object_feature_finder
          * alleyhoop_ros_msgs
          * (darknet_ros_msgs)[https://github.com/leggedrobotics/darknet_ros]
        - traffic_rules_feature_finder
          * alleyhoop_ros_msgs
          * OpenCV
        - (darknet_ros)[https://github.com/leggedrobotics/darknet_ros]

  3. slave
     * source code for the sensor and actuator controllers
     * scripts for running ROS sensors : LiDAR & Realsense camera
     * scripts for setting up the master, from setting up ROS to setting up libs for arduino
     * dependent on the following packages
       - arduino_ros_actuator_slave
         * (ROS_serial libs)[http://wiki.ros.org/rosserial]
         * std_msgs
         * sensor_msgs
       - arduino_ros_sensor_slave
         * (ROS_serial libs)[http://wiki.ros.org/rosserial]
         * (IMU_10DOF)[https://github.com/Seeed-Studio/IMU_10DOF]
         * sensor_msgs
         * std_msgs
       - raspi_ros_slave
         * (rplidar_ros)[http://wiki.ros.org/rplidar]
         * (realsense_ros)[http://wiki.ros.org/realsense2_camera]

The hardware components for which this software was made can be seen below:
