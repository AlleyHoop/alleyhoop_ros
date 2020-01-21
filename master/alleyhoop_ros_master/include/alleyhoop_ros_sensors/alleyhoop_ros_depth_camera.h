#ifndef ALLEYHOOPROSDEPTHCAMERA_H_
#define ALLEYHOOPROSDEPTHCAMERA_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>


namespace AlleyHoopROSSensors
{

    class DepthCamera : public AlleyHoopMVC::Sensor
    {
        public:      
            DepthCamera(std::string _name, ros::NodeHandle* _nh, std::string _point_cloud_topic, std::string _camera_info_topic);
            virtual ~DepthCamera() = default;

            void cameraInfoCallBack(const sensor_msgs::CameraInfo& msg);
            void pointCloudCallBack(const sensor_msgs::PointCloud2& msg);
            void update();
            sensor_msgs::PointCloud2 getData();

            const std::string image_topic_name;
            const std::string camera_info_topic_name;
            const std::string point_cloud_topic_name;

        protected:
            ros::Subscriber cam_info_sub;
            ros::Subscriber pcl_sub;
            ros::NodeHandle nh;

        private:
            sensor_msgs::PointCloud2 currentPcl;
    };

}

#endif //! ALLEYHOOPROSDEPTHCAMERA_H_