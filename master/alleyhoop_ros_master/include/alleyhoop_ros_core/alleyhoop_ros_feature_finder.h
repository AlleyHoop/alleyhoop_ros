#ifndef  ALLEYHOOPROSFEATUREFINDER_H_
#define  ALLEYHOOPROSFEATUREFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <cv_bridge/cv_bridge.h>
#include <list>



namespace AlleyHoopROSCore
{

    class FeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            FeatureFinder(ros::NodeHandle* _nh);
            ~FeatureFinder() = default;
            bool update();
            std::list<AlleyHoopROSUtils::Feature*>  findFeaturesOnImage(cv_bridge::CvImagePtr imagePtr);
            
            static bool verboseMode;

        protected:
            //ros
            ros::NodeHandle nh;

            //finder clients
            ros::ServiceClient image_feature_finder_client;
    };

}

#endif //!  ALLEYHOOPROSFEATUREFINDER_H_