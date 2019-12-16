#include "alleyhoop_ros/alleyhoop_feature_finder.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopAutonomousDriving
{

    AlleyHoopFeatureFinder::AlleyHoopFeatureFinder(ros::NodeHandle* _nh)
	: AutonomousDriving::Model(), nh(*_nh)
    {
    }

    void AlleyHoopFeatureFinder::update()
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