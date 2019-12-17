#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROSSensors
{
    AlleyHoopUltrasoon::AlleyHoopUltrasoon(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), topic_name(_topic), distance(0)
    {
        sub = nh.subscribe(topic_name, 1000, &AlleyHoopUltrasoon::callBack, this);
    }

    void AlleyHoopUltrasoon::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    int AlleyHoopUltrasoon::getData()
    {
        return distance;
    }

    void AlleyHoopUltrasoon::callBack(const std_msgs::UInt8 msg)
    {
        distance = msg.data;
    }
}