#ifndef  ALLEYHOOPROSCONTROLLER_H_
#define  ALLEYHOOPROSCONTROLLER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/controller.h"

#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasonic_sensor.h"
#include "alleyhoop_ros_sensors/alleyhoop_ros_mono_camera.h" 
#include "alleyhoop_ros_sensors/alleyhoop_ros_lidar.h"


namespace AlleyHoopROSCore
{
    class FeatureFinder;

    class Controller : public AlleyHoopMVC::Controller
    {

        public:
            Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v);
            ~Controller();
            bool update();

            static bool verboseDisplay;
            static bool verboseLog;

        protected:
            //ros
            ros::NodeHandle nh;

            //sensors
            AlleyHoopROSSensors::UltrasonicSensor* ultrasonic_sensor_1;
            AlleyHoopROSSensors::MonoCamera* mono_camera_1;
            AlleyHoopROSSensors::Lidar* lidar1;

            //finder
            FeatureFinder* featureFinder;
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
