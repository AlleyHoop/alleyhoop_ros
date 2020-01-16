#include "alleyhoop_ros_sensors/alleyhoop_ros_depth_camera.h"
#include <iostream>

namespace AlleyHoopROSSensors
{
    DepthCamera::DepthCamera(std::string _name, ros::NodeHandle* _nh, std::string _image_topic, std::string _point_cloud_topic, std::string _camera_info_topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), image_topic_name(_image_topic), point_cloud_topic_name(_point_cloud_topic), camera_info_topic_name(_camera_info_topic) , currentImagePtr(nullptr)
    {
        image_sub = nh.subscribe(_image_topic, 1, &DepthCamera::imageCallBack, this);
        cam_info_sub = nh.subscribe(_camera_info_topic, 1, &DepthCamera::cameraInfoCallBack, this);
        pcl_sub = nh.subscribe(_point_cloud_topic, 1, &DepthCamera::pointCloudCallBack, this);
    }

    void DepthCamera::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    cv_bridge::CvImagePtr DepthCamera::getData()
    {
        return currentImagePtr;
    }

    void DepthCamera::imageCallBack(const sensor_msgs::ImageConstPtr& msg)
    {
        currentImagePtr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
    }

    void DepthCamera::pointCloudCallBack(const sensor_msgs::PointCloud2& msg)
    {
     
    }

    void DepthCamera::cameraInfoCallBack(const sensor_msgs::CameraInfo& msg)
    {
        
    }
}