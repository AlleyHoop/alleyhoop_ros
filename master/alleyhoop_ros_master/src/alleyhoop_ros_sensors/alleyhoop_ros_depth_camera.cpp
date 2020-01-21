#include "alleyhoop_ros_sensors/alleyhoop_ros_depth_camera.h"
#include <iostream>

namespace AlleyHoopROSSensors
{
    DepthCamera::DepthCamera(std::string _name, ros::NodeHandle* _nh, std::string _point_cloud_topic, std::string _camera_info_topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), point_cloud_topic_name(_point_cloud_topic), camera_info_topic_name(_camera_info_topic)
    {
        pcl_sub = nh.subscribe(_point_cloud_topic, 1, &DepthCamera::pointCloudCallBack, this);
        cam_info_sub = nh.subscribe(_camera_info_topic, 1, &DepthCamera::cameraInfoCallBack, this);
    }

    void DepthCamera::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    sensor_msgs::PointCloud2 DepthCamera::getData()
    {
        return currentPcl;
    }

    void DepthCamera::pointCloudCallBack(const sensor_msgs::PointCloud2& msg)
    {
        currentPcl = msg;
    }

    
    void DepthCamera::cameraInfoCallBack(const sensor_msgs::CameraInfo& msg)
    {
        
    }
}