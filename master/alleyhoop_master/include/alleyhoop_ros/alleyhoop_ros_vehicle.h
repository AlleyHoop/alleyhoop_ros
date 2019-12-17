#ifndef ALLEYHOOPVEHICLE_H_
#define ALLEYHOOPVEHICLE_H_

#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
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

            //actuators
            AlleyHoopROSActuators::AlleyHoopLed* led1;
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_