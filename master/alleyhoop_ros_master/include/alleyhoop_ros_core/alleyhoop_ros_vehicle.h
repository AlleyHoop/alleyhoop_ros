#ifndef ALLEYHOOPROSVEHICLE_H_
#define ALLEYHOOPROSVEHICLE_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_motor.h"


namespace AlleyHoopROSCore
{

    class Vehicle : public AlleyHoopMVC::Vehicle
    {
        public:
            Vehicle(ros::NodeHandle* _nh);
            ~Vehicle() = default;
            bool update();

            //actuators
            AlleyHoopROSActuators::Led* led1;
            AlleyHoopROSActuators::Motor* steering_motor;
            AlleyHoopROSActuators::Motor* velocity_motor;

            static bool verboseMode;

        protected:
            //ros
            ros::NodeHandle nh;

            
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_