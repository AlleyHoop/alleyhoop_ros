#ifndef ALLEYFEATUREFINDER_H_
#define ALLEYFEATUREFINDER_H_

#include "alleyhoop_mvc/model.h"
#include "ros/ros.h"


namespace AlleyHoopAutonomousDriving
{

    class AlleyHoopFeatureFinder : public AutonomousDriving::Model
    {
        public:
            AlleyHoopFeatureFinder(ros::NodeHandle* _nh);
            ~AlleyHoopFeatureFinder() = default;
            bool update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYFEATUREFINDER_H_