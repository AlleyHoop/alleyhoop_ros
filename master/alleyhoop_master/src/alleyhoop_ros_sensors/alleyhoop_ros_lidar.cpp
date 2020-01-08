#include "alleyhoop_ros_sensors/alleyhoop_ros_lidar.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROSSensors
{
    Lidar::Lidar(std::string _name, ros::NodeHandle* _nh, std::string _laser_scan_topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), laser_scan_topic_name(_laser_scan_topic)
    {
        sub = nh.subscribe(laser_scan_topic_name, 1000, &Lidar::callBack, this);
    }

    void Lidar::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    void Lidar::getData()
    {
        
    }

    void Lidar::callBack(const sensor_msgs::LaserScan::ConstPtr& scan)
    {
        int count = scan->scan_time / scan->time_increment;
        ROS_INFO("I heard a laser scan %s[%d]:", scan->header.frame_id.c_str(), count);
        ROS_INFO("angle_range, %f, %f", RAD2DEG(scan->angle_min), RAD2DEG(scan->angle_max));
    
        for(int i = 0; i < count; i++) {
            float degree = RAD2DEG(scan->angle_min + scan->angle_increment * i);
            ROS_INFO(": [%f, %f]", degree, scan->ranges[i]);
        }
    }
}