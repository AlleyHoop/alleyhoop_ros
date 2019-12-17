#include "alleyhoop_ros/alleyhoop_ros_vehicle.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopVehicle::AlleyHoopVehicle(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Vehicle(), nh(*_nh)
    {
         //setup sensors
        led1 = new AlleyHoopROSActuators::AlleyHoopLed("led1_actuator", _nh, "/arduino_slave/led1_actuator");
        addActuator(led1);
    }

    bool AlleyHoopVehicle::update()
    {
        if (ros::ok())
        {
            
            updateActuators();
            return true;
        }

        std::cout << "roscore was not running!" << std::endl;
        return false;
    }

}
