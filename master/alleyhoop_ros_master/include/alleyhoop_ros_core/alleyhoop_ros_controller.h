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
#include "alleyhoop_ros_sensors/alleyhoop_ros_linetracker.h"


namespace AlleyHoopROSCore
{
    class FeatureFinder;
    class PathFinder;

    //* A ros controller implementation of the controller class from the alleyhoop_master package
    /**
    * Everything comes together in this class
    * 1. This class reads sensor data and passes them to the model to find features
    * 2. Based on a number of features the controller will instruct a path finder to find a path
    * 3. The controller will then instruct the vehicle to do some actions
    */
    class Controller : public AlleyHoopMVC::Controller
    {

        public:
            /*!
            * \brief The constructor for the controller class
            * \param _nh the nodehandle to publish data on
            * \param v a pointer to the vehicle that is to be controlled, is required by the controller base class
            */
            Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v);

            /*!
            * \brief the destructor will delete the member variables featurefinder and pathfinder where after the base class destructor will be called
            */
            ~Controller();

            /*!
            * \brief update function, is generally called from the main process
            * \todo actually control the vehicle
            */
            bool update();

            static bool verboseMode; /**< a static bool, when true more print messages will be displayed on the console*/

        protected:
            //ros
            ros::NodeHandle nh; /**< the nodehandle*/

            //sensors
            AlleyHoopROSSensors::UltrasonicSensor* ultrasonic_sensor_1; /**< a pointer to a ultrasonic_sensor for near-object detection */
            AlleyHoopROSSensors::MonoCamera* mono_camera_1; /**< a pointer to a mono camera for retrieving normal images */
            AlleyHoopROSSensors::DepthCamera* depth_camera_1; /**< a pointer to a depth camera for retrieving pointcloud data */
            AlleyHoopROSSensors::Lidar* lidar1; /**< a pointer to a laser tracer for depth measurement */
            AlleyHoopROSSensors::Imu* imu; /**< a pointer to a intertial measurement unit for retrieving accelaration, velocity and angular movement data */
            AlleyHoopROSSensors::LineTracker* linetracker_left; /**< a pointer to the left line tracker */
            AlleyHoopROSSensors::LineTracker* linetracker_right; /**< a pointer to the right line tracker */

            //finder
            FeatureFinder* featureFinder; /**< a pointer to a feature finder */
            PathFinder* pathFinder; /**< a pointer to a pathfinder */
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
