#include "alleyhoop_ros/alleyhoop_ros_feature_finder.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopFeatureFinder::AlleyHoopFeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
    }

    bool AlleyHoopFeatureFinder::update()
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

        std::cout << "program terminated" << std::endl;
        return false;
    }

}