#ifndef  ALLEYHOOPROSCONTROLLER_H_
#define  ALLEYHOOPROSCONTROLLER_H_

#include "alleyhoop_mvc/controller.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include "ros/ros.h"


namespace AlleyHoopROS
{
    class AlleyHoopController : public AlleyHoopMVC::Controller
    {
        public:
            AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v);
            ~AlleyHoopController() = default;
            bool update();

        protected:
            //ros
            ros::NodeHandle nh;

            //sensors
            AlleyHoopROSSensors::AlleyHoopUltrasoon* ultrasoon_sensor;
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
