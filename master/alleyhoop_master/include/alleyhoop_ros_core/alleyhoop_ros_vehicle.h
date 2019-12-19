#ifndef ALLEYHOOPVEHICLE_H_
#define ALLEYHOOPVEHICLE_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_motor.h"


namespace AlleyHoopROS
{

    class AlleyHoopVehicle : public AlleyHoopMVC::Vehicle
    {
        public:
            AlleyHoopVehicle(ros::NodeHandle* _nh);
            ~AlleyHoopVehicle() = default;
            bool update();

            //actuators
            AlleyHoopROSActuators::AlleyHoopLed* led1;
            AlleyHoopROSActuators::AlleyHoopMotor* steering_motor;
            AlleyHoopROSActuators::AlleyHoopMotor* velocity_motor;

        protected:
            //ros
            ros::NodeHandle nh;

            
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_