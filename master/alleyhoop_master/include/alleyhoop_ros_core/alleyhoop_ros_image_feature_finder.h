#ifndef  ALLEYHOOPROSIMAGEFEATUREFINDER_H_
#define  ALLEYHOOPROSIMAGEFEATUREFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <cv_bridge/cv_bridge.h>



namespace AlleyHoopROS
{

    class AlleyHoopImageFeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            AlleyHoopImageFeatureFinder(ros::NodeHandle* _nh);
            ~AlleyHoopImageFeatureFinder() = default;
            bool update();
            AlleyHoopROSUtils::AlleyHoopFeature* findFeatures(cv_bridge::CvImagePtr imagePtr);
            
        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSIMAGEFEATUREFINDER_H_