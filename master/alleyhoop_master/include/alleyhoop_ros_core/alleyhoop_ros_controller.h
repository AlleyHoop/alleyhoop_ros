#ifndef  ALLEYHOOPROSCONTROLLER_H_
#define  ALLEYHOOPROSCONTROLLER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/controller.h"

#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasoon.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_mono_camera.h" 
#include "alleyhoop_ros_sensors/alleyhoop_ros_lidar.h"


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
            AlleyHoopROSSensors::AlleyHoopMonoCamera* mono_camera_1;
            AlleyHoopROSSensors::AlleyHoopLidar* lidar1;

            //finder
            AlleyHoopImageFeatureFinder imageFeatureFinder;
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
