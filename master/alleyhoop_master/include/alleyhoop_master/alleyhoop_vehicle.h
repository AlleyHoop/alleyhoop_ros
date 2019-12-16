#ifndef ALLEYHOOPVEHICLE_H_
#define ALLEYHOOPVEHICLE_H_

#include "alleyhoop_master/vehicle.h"
#include "ros/ros.h"


namespace AutonomousDriving
{

    class AlleyHoopVehicle : public Vehicle
    {
        public:
            AlleyHoopVehicle(ros::NodeHandle* _nh);
            ~AlleyHoopVehicle() = default;
            void update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPVEHICLE_H_