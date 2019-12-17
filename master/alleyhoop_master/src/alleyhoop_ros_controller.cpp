#include "alleyhoop_ros/alleyhoop_ros_controller.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopController::AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh)
    {
        //setup sensors
        ultrasoon_sensor = new AlleyHoopROSSensors::AlleyHoopUltrasoon("ultrasoon_sensor", _nh, "ultrasoon_sensor_topic");
        addSensor(ultrasoon_sensor);
    }

    bool AlleyHoopController::update()
    {
        if (ros::ok())
        {
            // print text
            
            
            updateSensors(); //used for conventional implementation // for ros the following line, 'spinOnce()' is called instead 
            ros::spinOnce();
            return true;
        }

        std::cout << "roscore was not running!" << std::endl;
        return false;
    }

}
