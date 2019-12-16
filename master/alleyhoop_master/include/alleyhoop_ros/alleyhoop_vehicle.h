#ifndef ALLEYHOOPVEHICLE_H_
#define ALLEYHOOPVEHICLE_H_

#include "alleyhoop_mvc/vehicle.h"
#include "ros/ros.h"


namespace AlleyHoopAutonomousDriving
{

    class AlleyHoopVehicle : public AutonomousDriving::Vehicle
    {
        public:
            AlleyHoopVehicle(ros::NodeHandle* _nh);
            ~AlleyHoopVehicle() = default;
            bool update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPVEHICLE_H_