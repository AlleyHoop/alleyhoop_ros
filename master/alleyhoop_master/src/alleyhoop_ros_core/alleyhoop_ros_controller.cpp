#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"

#include <sstream>
#include <iostream>
#include <list>
#include <cv_bridge/cv_bridge.h>


namespace AlleyHoopROSCore
{
    bool Controller::verboseDisplay = false;
    bool Controller::verboseLog = false;

    Controller::Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh), imageFeatureFinder(_nh)
    {
        //setup sensors, add to controller base class for life line managing and update routine
        ultrasonic_sensor_1 = new AlleyHoopROSSensors::UltrasonicSensor("ultrasoon_sensor", _nh, "/arduino_slave/ultrasoon_sensor");
        addSensor(ultrasonic_sensor_1);

        mono_camera_1 = new AlleyHoopROSSensors::MonoCamera("mono_camera_1", _nh, "/raspi_camera/image_raw", "/raspi_camera/camera_info");
        addSensor(mono_camera_1);

        lidar1 = new AlleyHoopROSSensors::Lidar("lidar1", _nh, "/scan");
        addSensor(lidar1);
    }

    bool Controller::update()
    {
        if (ros::ok())
        {
            //update routinely
            updateSensors(); //used for conventional implementation // for ros the following line, 'spinOnce()' is called instead 
            ros::spinOnce();

            //get sensors data
            int ultrasonic_sensor_data = ultrasonic_sensor_1->getData();
            cv_bridge::CvImagePtr image_data = mono_camera_1->getData();

            //find features
            std::list<AlleyHoopROSUtils::Feature*> features = imageFeatureFinder.findFeatures(image_data);

            //make desicions based on features
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = features.begin(); feature_iter != features.end(); feature_iter++)
            {
                if(verboseLog)
                {
                    std::cout << "found a feature with type " + std::to_string((*feature_iter)->featureType) << std::endl;
                }
            }

            // control the actuators
            if(AlleyHoopROSCore::Vehicle* ah_vehicle = dynamic_cast<AlleyHoopROSCore::Vehicle*>(vehicle))
            {
                //turn on led
                if(ultrasonic_sensor_data < 30 && ultrasonic_sensor_data > 0)
                {
                    ah_vehicle->led1->setState(true);
                }
                else
                {
                    ah_vehicle->led1->setState(false);
                }
            }

            //save and cleanup
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = features.begin(); feature_iter != features.end(); feature_iter++)
            {
                delete (*feature_iter);
            }

            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
