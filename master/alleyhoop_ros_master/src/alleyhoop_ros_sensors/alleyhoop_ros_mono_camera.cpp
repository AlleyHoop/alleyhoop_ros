#include "alleyhoop_ros_sensors/alleyhoop_ros_mono_camera.h"
#include <iostream>

namespace AlleyHoopROSSensors
{
    MonoCamera::MonoCamera(std::string _name, ros::NodeHandle* _nh, std::string _image_topic, std::string _camera_info_topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), image_topic_name(_image_topic), camera_info_topic_name(_camera_info_topic) , currentImagePtr(nullptr)
    {
        sub = nh.subscribe(_image_topic, 1, &MonoCamera::callBack, this);
    }

    void MonoCamera::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    cv_bridge::CvImagePtr MonoCamera::getData()
    {
        return currentImagePtr;
    }

    void MonoCamera::callBack(const sensor_msgs::ImageConstPtr& msg)
    {
        currentImagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }
}