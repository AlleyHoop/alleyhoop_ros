#ifndef  ALLEYHOOPROSIMAGEFEATUREFINDER_H_
#define  ALLEYHOOPROSIMAGEFEATUREFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"

namespace AlleyHoopROS
{

    class AlleyHoopImageFeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            AlleyHoopImageFeatureFinder(ros::NodeHandle* _nh);
            ~AlleyHoopImageFeatureFinder() = default;
            bool update();

        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSIMAGEFEATUREFINDER_H_