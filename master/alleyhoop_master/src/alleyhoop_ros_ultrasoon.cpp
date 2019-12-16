#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROSSensors
{

    AlleyHoopUltrasoon::AlleyHoopUltrasoon(ros::NodeHandle* _nh, std::string _name, std::string _topic)
	: AlleyHooprOS::Sensor(_nh, _name, _topic)
    {

    }

    void sensorDataCallBack()
    {
        
    }

}