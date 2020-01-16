#ifndef ALLEYHOOPROSDEPTHCAMERA_H_
#define ALLEYHOOPROSDEPTHCAMERA_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>


namespace AlleyHoopROSSensors
{

    class DepthCamera : public AlleyHoopMVC::Sensor
    {
        public:      
            DepthCamera(std::string _name, ros::NodeHandle* _nh, std::string _image_topic, std::string _point_cloud_topic, std::string _camera_info_topic);
            virtual ~DepthCamera() = default;

            void imageCallBack(const sensor_msgs::ImageConstPtr& msg);
            void cameraInfoCallBack(const sensor_msgs::CameraInfo& msg);
            void pointCloudCallBack(const sensor_msgs::PointCloud2& msg);
            void update();
            cv_bridge::CvImagePtr getData();

            const std::string image_topic_name;
            const std::string camera_info_topic_name;
            const std::string point_cloud_topic_name;

        protected:
            ros::Subscriber image_sub;
            ros::Subscriber cam_info_sub;
            ros::Subscriber pcl_sub;
            ros::NodeHandle nh;

        private:
            cv_bridge::CvImagePtr currentImagePtr;
    };

}

#endif //! ALLEYHOOPROSDEPTHCAMERA_H_