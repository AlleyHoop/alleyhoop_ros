#ifndef  ALLEYHOOPROSCONTROLLER_H_
#define  ALLEYHOOPROSCONTROLLER_H_

//required includes
#include <ros/ros.h>
#include "alleyhoop_mvc/controller.h"

//sensor headers
#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasonic_sensor.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_mono_camera.h" 
#include "alleyhoop_ros_sensors/alleyhoop_ros_lidar.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_depth_camera.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_imu.h"


namespace AlleyHoopROSCore
{
    class FeatureFinder;
    class PathFinder;

    class Controller : public AlleyHoopMVC::Controller
    {

        public:
            Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v);
            ~Controller();
            bool update();

            static bool verboseMode;

        protected:
            //ros
            ros::NodeHandle nh;

            //sensors
            AlleyHoopROSSensors::UltrasonicSensor* ultrasonic_sensor_1;
            AlleyHoopROSSensors::MonoCamera* mono_camera_1;
            AlleyHoopROSSensors::DepthCamera* depth_camera_1;
            AlleyHoopROSSensors::Lidar* lidar1;
            AlleyHoopROSSensors::Imu* imu;

            //finder
            FeatureFinder* featureFinder;
            PathFinder* pathFinder;
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
