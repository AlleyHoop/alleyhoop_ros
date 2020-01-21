#ifndef ALLEYHOOPROSVEHICLE_H_
#define ALLEYHOOPROSVEHICLE_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_motor.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

namespace AlleyHoopROSCore
{

    class Vehicle : public AlleyHoopMVC::Vehicle
    {
        public:
            Vehicle(ros::NodeHandle* _nh);
            ~Vehicle() = default;
            bool update();

            static bool verboseMode;

            //actuators
            AlleyHoopROSActuators::Led* led1;
            AlleyHoopROSActuators::Led* led2;
            AlleyHoopROSActuators::Motor* steering_motor;
            AlleyHoopROSActuators::Motor* velocity_motor;

            //positioning and movement
            AlleyHoopROSUtils::Transform transform;
            AlleyHoopROSUtils::Transform destination;
            
        protected:
            //ros
            ros::NodeHandle nh;

            int maxSpeed;
            int currentSpeed;
            

            
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_