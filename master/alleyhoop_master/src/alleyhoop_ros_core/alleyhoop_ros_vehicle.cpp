#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopVehicle::AlleyHoopVehicle(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Vehicle(), nh(*_nh)
    {
         //setup sensors
        led1 = new AlleyHoopROSActuators::AlleyHoopLed("led1", _nh, "/arduino_slave/led1_actuator");
        addActuator(led1);

        steering_motor = new AlleyHoopROSActuators::AlleyHoopMotor("steering_motor", _nh, "/arduino_slave/servo");
        addActuator(steering_motor);

        velocity_motor = new AlleyHoopROSActuators::AlleyHoopMotor("velocity_motor", _nh, "/arduino_slave/esc");
        addActuator(velocity_motor);
    }

    bool AlleyHoopVehicle::update()
    {
        if (ros::ok())
        {
            updateActuators();
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
