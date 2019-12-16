#ifndef ALLEYFEATUREFINDER_H_
#define ALLEYFEATUREFINDER_H_

#include "alleyhoop_master/model.h"
#include "ros/ros.h"


namespace AutonomousDriving
{

    class AlleyHoopFeatureFinder : public Model
    {
        public:
            AlleyHoopFeatureFinder(ros::NodeHandle* _nh);
            ~AlleyHoopFeatureFinder() = default;
            void update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYFEATUREFINDER_H_