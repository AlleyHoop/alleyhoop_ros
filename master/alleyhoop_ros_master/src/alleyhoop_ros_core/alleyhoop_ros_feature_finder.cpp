#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"
#include "alleyhoop_ros_msgs/FindFeaturesOnImage.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool FeatureFinder::verboseDisplay = false;
    bool FeatureFinder::verboseLog = false;

    FeatureFinder::FeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
        image_feature_finder_client = nh.serviceClient<alleyhoop_ros_msgs::FindFeaturesOnImage>("example_feature_finder");
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
        //ensure an image was sent
        if(imagePtr == nullptr)
        {
            return std::list<AlleyHoopROSUtils::Feature*>();
        }

        //create service msg
        alleyhoop_ros_msgs::FindFeaturesOnImage srv;
        imagePtr->toImageMsg(srv.request.image);

        //call to client with msg
        if (!image_feature_finder_client.call(srv))
        {
            ROS_ERROR("Failed to call service example_feature_finder");
            return std::list<AlleyHoopROSUtils::Feature*>();
        }

        //read responce
        if(srv.response.step < 1)
        {
            ROS_ERROR("no feautes were found");
            return std::list<AlleyHoopROSUtils::Feature*>();
        }
        else
        {
            for(int i = 0; i < srv.response.features.size(); i+srv.response.step)
            {
                if(verboseLog)
                    std::cout << "found feature at (" << srv.response.features[i] << "," << srv.response.features[i+1] << "," << srv.response.features[i+2] << "," << srv.response.features[i+3] << ")" << std::endl;
                //convert to features
                //TODO!!!!!!!!!!!!
            }
        }
        
        return std::list<AlleyHoopROSUtils::Feature*>();
    }

}