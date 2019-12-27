#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopImageFeatureFinder::AlleyHoopImageFeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
    }

    bool AlleyHoopImageFeatureFinder::update()
    {
        if (ros::ok())
        {
            
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}