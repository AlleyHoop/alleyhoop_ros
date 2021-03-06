#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool Vehicle::verboseMode = false;

    Vehicle::Vehicle(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Vehicle(), nh(*_nh), maxSpeed(0), currentSpeed(0)
    {
        //read params, if fail set a default value
        std::string led1_topic_name;
        if(!nh.getParam("AlleyHoop_Actuators/Led1_TopicName",led1_topic_name))
            led1_topic_name = "/slave/led1";

        std::string led2_topic_name;
        if(!nh.getParam("AlleyHoop_Actuators/Led2_TopicName",led2_topic_name))
            led2_topic_name = "/slave/led2";
        
        std::string steering_motor_topic_name;
        if(!nh.getParam("AlleyHoop_Actuators/SteeringMotor_TopicName",steering_motor_topic_name))
            steering_motor_topic_name = "/slave/servo";

        std::string velocity_motor_topic_name;
        if(!nh.getParam("AlleyHoop_Actuators/VelocityMotor_TopicName",velocity_motor_topic_name))
            velocity_motor_topic_name = "/slave/esc";

        //setup actuators
        led1 = new AlleyHoopROSActuators::Led("led1", _nh, led1_topic_name);
        addActuator(led1);

        led2 = new AlleyHoopROSActuators::Led("led2", _nh, led2_topic_name);
        addActuator(led2);

        steering_motor = new AlleyHoopROSActuators::Motor("steering_motor", _nh, steering_motor_topic_name);
        addActuator(steering_motor);

        velocity_motor = new AlleyHoopROSActuators::Motor("velocity_motor", _nh, velocity_motor_topic_name);
        addActuator(velocity_motor);
    }


    bool Vehicle::update()
    {
        if (ros::ok())
        {
            //calculate speed


            //update actuators
            updateActuators();

            //update view
            
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
