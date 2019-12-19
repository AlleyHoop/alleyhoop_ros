#ifndef  ALLEYHOOPROSFEATUREFINDER_H_
#define  ALLEYHOOPROSFEATUREFINDER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/model.h"

namespace AlleyHoopROS
{

    class AlleyHoopFeatureFinder : public AlleyHoopMVC::Model
    {
        public:
            AlleyHoopFeatureFinder(ros::NodeHandle* _nh);
            ~AlleyHoopFeatureFinder() = default;
            bool update();

        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSFEATUREFINDER_H_