#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool Vehicle::verboseDisplay = false;
    bool Vehicle::verboseLog = false;

    Vehicle::Vehicle(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Vehicle(), nh(*_nh)
    {
         //setup sensors
        led1 = new AlleyHoopROSActuators::Led("led1", _nh, "/arduino_slave/led1_actuator");
        addActuator(led1);

        steering_motor = new AlleyHoopROSActuators::Motor("steering_motor", _nh, "/arduino_slave/servo");
        addActuator(steering_motor);

        velocity_motor = new AlleyHoopROSActuators::Motor("velocity_motor", _nh, "/arduino_slave/esc");
        addActuator(velocity_motor);
    }

    bool Vehicle::update()
    {
        if (ros::ok())
        {
            //update actuators
            updateActuators();

            //update view
            
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
