#ifndef ALLEYHOOPROSVEHICLE_H_
#define ALLEYHOOPROSVEHICLE_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "alleyhoop_ros_actuators/alleyhoop_ros_motor.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

namespace AlleyHoopROSCore
{
    //* A ros vehicle implementation of the vehicle class from the alleyhoop_master package
    /**
    * This class instructs the actuators to publish there actuator data so that the actual vehicle moves.
    */

    class Vehicle : public AlleyHoopMVC::Vehicle
    {
        public:
            /*!
            * \brief The constructor for the vehicle class
            * \param _nh the nodehandle to publish data on
            */
            Vehicle(ros::NodeHandle* _nh);

            /*!
            * \brief The default destructor
            */
            ~Vehicle() = default;

            /*!
            * \brief The update function, generally called from the main process
            */
            bool update();

            static bool verboseMode; /**< a static bool, when true more print messages will be displayed on the console*/

            //actuators
            AlleyHoopROSActuators::Led* led1; /**< a pointer to a led */
            AlleyHoopROSActuators::Led* led2; /**< a pointer to a led */
            AlleyHoopROSActuators::Motor* steering_motor; /**< a pointer to the motor for steering the vehicle */
            AlleyHoopROSActuators::Motor* velocity_motor; /**< a pointer to the motor for moving the vehicle */

            //positioning and movement
            AlleyHoopROSUtils::Transform transform; /**< the current position and rotation of the vehicle */
            AlleyHoopROSUtils::Transform destination; /**< the destination position and rotation of the vehicle */
            
        protected:
            //ros
            ros::NodeHandle nh; /**< the nodehandle */

            int maxSpeed = 100; /**< the maximum speed the vehicle is allowed to move */
            int moveDirection = 0; /**< the direction to move, -1 = backwards, 0 = brake, 1 = fowards */
            int currentSpeed = 0; /**< the current speed of the vehicle */
            int steer = 0;  /**< the angle to turn the steering motor */
            

            
    };

}

#endif //!  ALLEYHOOPROSVEHICLE_H_