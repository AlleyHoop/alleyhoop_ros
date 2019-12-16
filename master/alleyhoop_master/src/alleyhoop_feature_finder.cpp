#include "alleyhoop_master/alleyhoop_feature_finder.h"
#include <sstream>
#include <iostream>

namespace AutonomousDriving
{

    AlleyHoopFeatureFinder::AlleyHoopFeatureFinder(ros::NodeHandle* _nh)
	: Model(), nh(*_nh)
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
        }
        else
        {
            std::cout << "ros was not running!" << std::endl;
        }
    }

}