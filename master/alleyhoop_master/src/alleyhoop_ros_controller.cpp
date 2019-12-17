#include "alleyhoop_ros/alleyhoop_ros_controller.h"
#include "alleyhoop_ros/alleyhoop_ros_vehicle.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopController::AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh)
    {
        //setup sensors
        ultrasoon_sensor = new AlleyHoopROSSensors::AlleyHoopUltrasoon("ultrasoon_sensor", _nh, "/arduino_slave/ultrasoon_sensor");
        addSensor(ultrasoon_sensor);
    }

    bool AlleyHoopController::update()
    {
        if (ros::ok())
        {
            // make decisions
            if(AlleyHoopROS::AlleyHoopVehicle* ah_vehicle = dynamic_cast<AlleyHoopROS::AlleyHoopVehicle*>(vehicle))
            {
                if(ultrasoon_sensor->getData() < 30)
                {
                    ah_vehicle->led1->setState(true);
                    ROS_INFO("Set data led state to TRUE");
                }
                else
                {
                    ah_vehicle->led1->setState(false);
                    ROS_INFO("Set data led state to FALSE");
                }
            }

            //update routinely
            updateSensors(); //used for conventional implementation // for ros the following line, 'spinOnce()' is called instead 
            ros::spinOnce();
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
