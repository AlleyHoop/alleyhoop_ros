#include "alleyhoop_ros/alleyhoop_controller.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopAutonomousDriving
{

    AlleyHoopController::AlleyHoopController(ros::NodeHandle* _nh, AutonomousDriving::Vehicle* v)
	: AutonomousDriving::Controller(v), nh(*_nh)
    {
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
