#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"

#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"
#include "alleyhoop_ros_core/alleyhoop_ros_path_finder.h"

#include "alleyhoop_ros_utils/alleyhoop_ros_feature.h"
#include "alleyhoop_ros_utils/alleyhoop_ros_math.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/PointCloud2.h>

//std
#include <iostream>
#include <list>


namespace AlleyHoopROSCore
{
    bool Controller::verboseMode = false;

    Controller::Controller(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh)
    {
        //read params, if fail set a default value
        std::string ultrasonic_sensor_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/UltrasonicSensor_TopicName",ultrasonic_sensor_topic_name))
            ultrasonic_sensor_topic_name = "/arduino_sensor_slave/ultrasonic_sensor";
        
        std::string mono_camera_image_raw_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/MonoCameraImageRaw_TopicName",mono_camera_image_raw_topic_name))
            mono_camera_image_raw_topic_name = "/camera/color/image_raw";

        std::string mono_camera_info_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/MonoCameraInfo_TopicName",mono_camera_info_topic_name))
            mono_camera_info_topic_name = "/camera/color/camera_info";

        std::string lidar_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/Lidar_TopicName",lidar_topic_name))
            lidar_topic_name = "/scan";

        std::string depth_camera_info_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/DepthCameraInfo_TopicName",depth_camera_info_topic_name))
            depth_camera_info_topic_name = "/camera/depth/camera_info";

        std::string depth_camera_pcl_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/DepthCameraPcl_TopicName",depth_camera_pcl_topic_name))
            depth_camera_pcl_topic_name = "/camera/depth/color/points";

        std::string imu_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/ImuSensor_TopicName",imu_topic_name))
            imu_topic_name = "/arduino_sensor_slave/imu_sensor";

        std::string linetracker_left_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/LineTrackerLeft_TopicName",linetracker_left_topic_name))
            linetracker_left_topic_name = "/arduino_sensor_slave/linetracker_left";

        std::string linetracker_right_topic_name;
        if(!nh.getParam("AlleyHoop_Sensors/LineTrackerRight_TopicName",linetracker_right_topic_name))
            linetracker_right_topic_name = "/arduino_sensor_slave/linetracker_right";
        
        //setup sensors, add to controller base class for life line managing and update routine
        ultrasonic_sensor_1 = new AlleyHoopROSSensors::UltrasonicSensor("ultrasonic_sensor", _nh, ultrasonic_sensor_topic_name);
        addSensor(ultrasonic_sensor_1);
        if(verboseMode) std::cout <<  " ultrasonic_sensor subscribed to " << ultrasonic_sensor_topic_name << std::endl;

        mono_camera_1 = new AlleyHoopROSSensors::MonoCamera("mono_camera_1", _nh, mono_camera_image_raw_topic_name, mono_camera_info_topic_name);
        addSensor(mono_camera_1);
        if(verboseMode) std::cout <<  " mono_camera_1 subscribed to " << mono_camera_image_raw_topic_name << " and " << mono_camera_info_topic_name << std::endl;

        lidar1 = new AlleyHoopROSSensors::Lidar("lidar1", _nh, lidar_topic_name);
        addSensor(lidar1);
        if(verboseMode) std::cout <<  " lidar1 subscribed to " << lidar_topic_name << std::endl;

        depth_camera_1 = new AlleyHoopROSSensors::DepthCamera("depth_camera_1", _nh, depth_camera_pcl_topic_name, depth_camera_info_topic_name);
        addSensor(depth_camera_1);
        if(verboseMode) std::cout <<  " depth_camera_1 subscribed to " << depth_camera_pcl_topic_name << " and " << depth_camera_info_topic_name << std::endl;

        imu = new AlleyHoopROSSensors::Imu("imu", _nh, imu_topic_name);
        addSensor(imu);
        if(verboseMode) std::cout <<  " imu subscribed to " << imu_topic_name << std::endl;

        linetracker_left = new AlleyHoopROSSensors::LineTracker("linetracker_left", _nh, linetracker_left_topic_name);
        addSensor(linetracker_left);
        if(verboseMode) std::cout <<  " linetracker_left subscribed to " << linetracker_left_topic_name << std::endl;

        linetracker_right = new AlleyHoopROSSensors::LineTracker("linetracker_right", _nh, linetracker_right_topic_name);
        addSensor(linetracker_right);
        if(verboseMode) std::cout <<  " linetracker_right subscribed to " << linetracker_right_topic_name << std::endl;

        //setup feature finders
        featureFinder = new FeatureFinder(_nh);
        
        //setup path finders
        AlleyHoopROSUtils::Vector3 _startPosition;
        AlleyHoopROSUtils::Vector3 _nodeSizes(2, 2, 2);
        pathFinder = new PathFinder(_nh, _startPosition, _nodeSizes);
    }

    Controller::~Controller()
    {
        if(featureFinder != nullptr)
        {
            std::cout << "deleted feature finder" << std::endl;
            delete featureFinder;
        }

        if(pathFinder != nullptr)
        {
            std::cout << "deleted path finder" << std::endl;
            delete pathFinder;
        }
    }

    bool Controller::update()
    {
        if (ros::ok())
        {
            //update routinely
            if(verboseMode) std::cout <<  "-------------" << "\nController: updating sensors...." << std::endl;
            updateSensors(); //used for conventional implementation // for ros the following line, 'spinOnce()' is called instead 
            ros::spinOnce();

            //get sensors data
            int ultrasonic_sensor_data = ultrasonic_sensor_1->getData(); 
            cv_bridge::CvImagePtr image_data_foward = mono_camera_1->getData();
            sensor_msgs::PointCloud2 pcl_data_foward = depth_camera_1->getData();

            //find objects
            if(verboseMode) std::cout <<  "-------------" << "\nController: finding features...." << std::endl;
            std::list<AlleyHoopROSUtils::Feature*> objects;
            if(featureFinder->findObjectsOnImage(objects, image_data_foward))
            {
                //featureFinder->processDepthDataOnFeatures(objects, pcl_data_foward);
            }
            
            //TODO base the signs on cropped versions of the found objects
            std::list<AlleyHoopROSUtils::Feature*> trafficSigns;
            if(featureFinder->findTrafficRulesOnImage(trafficSigns, image_data_foward))
            {

            }

            //find the road
            std::list<AlleyHoopROSUtils::Feature*> roadFeatures;
            featureFinder->findRoadOnImage(roadFeatures, image_data_foward);
            
            //make decisions
            if(verboseMode) std::cout <<  "-------------" << "\nController: making desicions...." << std::endl;
            if(AlleyHoopROSCore::Vehicle* ah_vehicle = dynamic_cast<AlleyHoopROSCore::Vehicle*>(vehicle))
            {

                //fix feature transforms to reference from the center of the vehicle
                for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = objects.begin(); feature_iter != objects.end(); feature_iter++)
                {
                    
                }

                //!!TODO convert trafficrules features to actuator actions such as speed limit

  
                //find path to target position
                if(verboseMode) std::cout <<  "-------------" << "\nController: finding path...." << std::endl;
                //pathFinder->findPath(ah_vehicle->transform, ah_vehicle->destination, objects, roadFeatures);

                //!!TODO read the path and translate to motion for the motor
                //ah_vehicle->

                
                
                // <OLD> Ultrasonic sensor example
                if(ultrasonic_sensor_data < 30 && ultrasonic_sensor_data > 0)
                {
                    //turn on leds
                    ah_vehicle->led1->setState(true);
                    ah_vehicle->led2->setState(true);
                    ah_vehicle->velocity_motor->setData(-1);
                }
                else if(ultrasonic_sensor_data >= 30)
                {
                    //turn on led
                    ah_vehicle->led1->setState(false);
                    ah_vehicle->led2->setState(false);
                    ah_vehicle->velocity_motor->setData(1);
                }

            }

            //!!TODO save points of interest such us objects to track and merge them to list of features at the top



            //cleanup
            if(verboseMode) std::cout <<  "-------------" << "\nController: clearing features...." << std::endl;
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = objects.begin(); feature_iter != objects.end(); feature_iter++)
            {
                delete (*feature_iter);
            }
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = roadFeatures.begin(); feature_iter != roadFeatures.end(); feature_iter++)
            {
                delete (*feature_iter);
            }
            for(std::list<AlleyHoopROSUtils::Feature*>::iterator feature_iter = trafficSigns.begin(); feature_iter != trafficSigns.end(); feature_iter++)
            {
                delete (*feature_iter);
            }
            objects.clear();
            roadFeatures.clear();
            trafficSigns.clear();

            if(verboseMode) std::cout <<  "-------------" << "\n Controller: Succesfully executed actions...." << std::endl;
            return true;
        }

        std::cout <<  "-------------" << "Controller: program terminated" << std::endl;
        return false;
    }

}
