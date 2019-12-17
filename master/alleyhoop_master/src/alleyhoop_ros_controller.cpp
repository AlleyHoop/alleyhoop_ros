#include "alleyhoop_ros/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopController::AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh)
    {
        //setup sensors
        AlleyHoopROSSensors::AlleyHoopUltrasoon* ultrasoon_sensor = new AlleyHoopROSSensors::AlleyHoopUltrasoon("ultrasoon_sensor", _nh, "ultrasoon_sensor_topic");
        addSensor(ultrasoon_sensor);
    }

    bool AlleyHoopController::update()
    {
        if (ros::ok())
        {
            // print text
            std::stringstream ss;
            ss << "controller running..";
            ROS_INFO("%s", ss.str().c_str());
            ros::spinOnce();
            return true;
        }

        std::cout << "roscore was not running!" << std::endl;
        return false;
    }

}
