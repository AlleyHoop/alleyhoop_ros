#ifndef ALLEYHOOPVEHICLE_H_
#define ALLEYHOOPVEHICLE_H_

#include "alleyhoop_mvc/vehicle.h"
#include "ros/ros.h"


namespace AlleyHoopROS
{

    class AlleyHoopVehicle : public AlleyHoopMVC::Vehicle
    {
        public:
            AlleyHoopVehicle(ros::NodeHandle* _nh);
            ~AlleyHoopVehicle() = default;
            bool update();

        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_