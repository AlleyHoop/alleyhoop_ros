#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROSSensors
{

    AlleyHoopUltrasoon::AlleyHoopUltrasoon(ros::NodeHandle* _nh, std::string _name, std::string _topic)
	    : AlleyHoopROS::AlleyHoopSensor(_nh, _name, _topic)
    {

    }

    void sensorDataCallBack()
    {

    }

}