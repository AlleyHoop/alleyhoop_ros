#ifndef  ALLEYHOOPROSIMAGEFEATUREFINDER_H_
#define  ALLEYHOOPROSIMAGEFEATUREFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <cv_bridge/cv_bridge.h>
#include <list>



namespace AlleyHoopROSCore
{

    class ImageFeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            ImageFeatureFinder(ros::NodeHandle* _nh);
            ~ImageFeatureFinder() = default;
            bool update();
            std::list<AlleyHoopROSUtils::Feature*>  findFeatures(cv_bridge::CvImagePtr imagePtr);
            
            static bool verboseDisplay;
            static bool verboseLog;

        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSIMAGEFEATUREFINDER_H_