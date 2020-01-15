#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool FeatureFinder::verboseDisplay = false;
    bool FeatureFinder::verboseLog = false;

    FeatureFinder::FeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
    }

    bool FeatureFinder::update()
    {
        if (ros::ok())
        {
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

    std::list<AlleyHoopROSUtils::Feature*> FeatureFinder::findFeaturesOnImage(cv_bridge::CvImagePtr imagePtr)
    {   

        return std::list<AlleyHoopROSUtils::Feature*>();
    }

}