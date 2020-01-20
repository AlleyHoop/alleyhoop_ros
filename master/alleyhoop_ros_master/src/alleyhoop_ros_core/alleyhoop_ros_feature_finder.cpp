#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"
#include "alleyhoop_ros_msgs/FindFeaturesOnImage.h"

#include <string>
#include <vector>
#include <sstream>
#include <iostream>

namespace AlleyHoopROSCore
{
    bool FeatureFinder::verboseMode = false;

    FeatureFinder::FeatureFinder(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Model(), nh(*_nh)
    {
        //read params, if fail set a default value
        std::string traffic_rules_feature_finder_service;
        if(!nh.getParam("AlleyHoop_Models/TrafficRulesFeaturesOnImage_ServiceName",traffic_rules_feature_finder_service))
            traffic_rules_feature_finder_service = "example_feature_finder";

        std::string object_feature_finder_service;
        if(!nh.getParam("AlleyHoop_Models/ObjectFeaturesOnImage_ServiceName",object_feature_finder_service))
            object_feature_finder_service = "example_feature_finder";

        std::string road_feature_finder_service;
        if(!nh.getParam("AlleyHoop_Models/RoadFeaturesOnImage_ServiceName",road_feature_finder_service))
            road_feature_finder_service = "example_feature_finder";

        //setup feature finder
        traffic_rules_feature_finder_client = nh.serviceClient<alleyhoop_ros_msgs::FindFeaturesOnImage>(traffic_rules_feature_finder_service);
        object_feature_finder_client = nh.serviceClient<alleyhoop_ros_msgs::FindFeaturesOnImage>(object_feature_finder_service);
        road_feature_finder_client = nh.serviceClient<alleyhoop_ros_msgs::FindFeaturesOnImage>(road_feature_finder_service);

        //print
        std::cout << "created feature finder" << std::endl;
        if(verboseMode) std::cout <<  " feature finder subscribed to services: " << traffic_rules_feature_finder_service << " and " << object_feature_finder_service << " and " << road_feature_finder_service << std::endl;
    }

    bool FeatureFinder::processDepthDataOnFeatures(std::list<AlleyHoopROSUtils::Feature*>& features, sensor_msgs::PointCloud2& pcl)
    { 
        return false;
    }

    bool FeatureFinder::findTrafficRulesOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr)
    { 
        //ensure an image was sent
        if(imagePtr == nullptr)
        {
            return false;
        }

        //create service msg
        alleyhoop_ros_msgs::FindFeaturesOnImage srv;
        imagePtr->toImageMsg(srv.request.image);

        //call to client with msg
        if (!traffic_rules_feature_finder_client.call(srv))
        {
            if(verboseMode)
                ROS_ERROR("FeatureFinder: Failed to call service for traffic rules feature finder");
            return false;
        }

        //ensure that features were found
        if(srv.response.step < 1)
        {
            if(verboseMode)
            {
                std::cout << "FeatureFinder: no traffic features found" << std::endl;
            }
            return false;
        }
        
        //read response
        if(verboseMode) std::cout << "FeatureFinder: found " << srv.response.features.size()/srv.response.step << " traffic features. Size: " << srv.response.features.size() << " Step: " << srv.response.step << std::endl;
        if(srv.response.step == 4)
        {   
            for(size_t i = 0; i < srv.response.features.size(); i+=srv.response.step)
            {
                
                if(verboseMode) std::cout << "FeatureFinder: found traffic feature at (" << srv.response.features[i] << "," << srv.response.features[i+1] << "," << srv.response.features[i+2] << "," << srv.response.features[i+3] << ")" << std::endl;

                AlleyHoopROSUtils::Feature* f = new AlleyHoopROSUtils::Feature(AlleyHoopROSUtils::FeatureTypes::StaticObject);
                f->transform.position.x = srv.response.features[i];
                f->transform.position.y = srv.response.features[i+1];
                //TODO estimate position z value

                //TODO estimate rotational values

                f->halfExtents.x = srv.response.features[i+2];
                f->halfExtents.y = srv.response.features[i+3];
                //TODO estimate z half extents value

                //add the feature
                features.push_back(f);
            }

            return true;
        }

        return false;
        
    }

    bool FeatureFinder::findRoadOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr)
    { 
         //ensure an image was sent
        if(imagePtr == nullptr)
        {
            return false;
        }

        //create service msg
        alleyhoop_ros_msgs::FindFeaturesOnImage srv;
        imagePtr->toImageMsg(srv.request.image);

        //call to client with msg
        if (!road_feature_finder_client.call(srv))
        {
            if(verboseMode)
                ROS_ERROR("FeatureFinder: Failed to call service for road feature finder");
            return false;
        }

        //ensure that features were found
        if(srv.response.step < 1)
        {
            if(verboseMode)
            {
                std::cout << "FeatureFinder: no road found" << std::endl;
            }
            return false;
        }
        
        //read response
        if(verboseMode) std::cout << "FeatureFinder: found " << srv.response.features.size()/srv.response.step << " road features. Size: " << srv.response.features.size() << " Step: " << srv.response.step << std::endl;
        if(srv.response.step == 4)
        {
            for(size_t i = 0; i < srv.response.features.size(); i+=srv.response.step)
            {
                if(verboseMode) std::cout << "FeatureFinder: found road at (" << srv.response.features[i] << "," << srv.response.features[i+1] << "," << srv.response.features[i+2] << "," << srv.response.features[i+3] << ")" << std::endl;

            }

            return true;
        }
        
        return false;
    }

    bool FeatureFinder::findObjectsOnImage(std::list<AlleyHoopROSUtils::Feature*>& features, cv_bridge::CvImagePtr& imagePtr)
    {   
        //ensure an image was sent
        if(imagePtr == nullptr)
        {
            return false;
        }

        //create service msg
        alleyhoop_ros_msgs::FindFeaturesOnImage srv;
        imagePtr->toImageMsg(srv.request.image);

        //call to client with msg
        if (!object_feature_finder_client.call(srv))
        {
            if(verboseMode)
                ROS_ERROR("FeatureFinder: Failed to call service for object feature finder");
            return false;
        }

        //ensure that features were found
        if(srv.response.step < 1)
        {
            if(verboseMode)
            {
                std::cout << "FeatureFinder: no objects found" << std::endl;
            }
            return false;
        }
        
        //read response
        if(verboseMode) std::cout << "FeatureFinder: found " << srv.response.features.size()/srv.response.step << " objects. Size: " << srv.response.features.size() << " Step: " << srv.response.step << std::endl;
        if(srv.response.step == 4)
        {
            for(size_t i = 0; i < srv.response.features.size(); i+=srv.response.step)
            {
                if(verboseMode) std::cout << "FeatureFinder: found object at (" << srv.response.features[i] << "," << srv.response.features[i+1] << "," << srv.response.features[i+2] << "," << srv.response.features[i+3] << ")" << std::endl;

                AlleyHoopROSUtils::Feature* f = new AlleyHoopROSUtils::Feature(AlleyHoopROSUtils::FeatureTypes::StaticObject);
                f->transform.position.x = srv.response.features[i];
                f->transform.position.y = srv.response.features[i+1];
                //TODO estimate position z value

                //TODO estimate rotational values

                f->halfExtents.x = srv.response.features[i+2];
                f->halfExtents.y = srv.response.features[i+3];
                //TODO estimate z half extents value

                //add the feature
                features.push_back(f);
            }

            return true;
        }
        
        return false;
    }

}