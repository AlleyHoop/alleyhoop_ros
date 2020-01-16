#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"
#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"

#include <sstream>
#include <iostream>
#include <list>
#include <cv_bridge/cv_bridge.h>


namespace AlleyHoopROSCore
{
    bool Controller::verboseMode = false;

    Controller::Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh)
    {
        //read params, if fail set a default value
        std::string ultrasonic_sensor_topic_name;
        if(!nodeHandle.getParam("AlleyHoop_Sensors/UltrasonicSensor_TopicName",ultrasonic_sensor_topic_name))
            ultrasonic_sensor_topic_name = "/arduino_slave/ultrasonic_sensor";
        
        std::string mono_camera_image_raw_topic_name;
        if(!nodeHandle.getParam("AlleyHoop_Sensors/MonoCameraImageRaw_TopicName",mono_camera_image_raw_topic_name))
            mono_camera_image_raw_topic_name = "/raspi_camera/image_raw";

        std::string mono_camera_info_topic_name;
        if(!nodeHandle.getParam("AlleyHoop_Sensors/MonoCameraInfo_TopicName",mono_camera_info_topic_name))
            mono_camera_info_topic_name = "/raspi_camera/camera_info";

        std::string lidar_topic_name;
        if(!nodeHandle.getParam("AlleyHoop_Sensors/Lidar_TopicName",lidar_topic_name))
            lidar_topic_name = "/scan";


        //setup sensors, add to controller base class for life line managing and update routine
        ultrasonic_sensor_1 = new AlleyHoopROSSensors::UltrasonicSensor("ultrasonic_sensor", _nh, ultrasonic_sensor_topic_name);
        addSensor(ultrasonic_sensor_1);

        mono_camera_1 = new AlleyHoopROSSensors::MonoCamera("mono_camera_1", _nh, mono_camera_image_raw_topic_name, mono_camera_info_topic_name);
        addSensor(mono_camera_1);

        lidar1 = new AlleyHoopROSSensors::Lidar("lidar1", _nh, lidar_topic_name);
        addSensor(lidar1);

        //setup feature finders
        featureFinder = new FeatureFinder(_nh);
    }

    Controller::~Controller()
    {
        if(featureFinder != nullptr)
        {
            std::cout << "deleted finder" << std::endl;
            delete featureFinder;
        }
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
            std::list<AlleyHoopROSUtils::Feature*> features = featureFinder->findFeaturesOnImage(image_data);

            //make desicions based on features
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = features.begin(); feature_iter != features.end(); feature_iter++)
            {
                if(verboseMode)
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
