#ifndef ALLEYHOOPROSDEPTHCAMERA_H_
#define ALLEYHOOPROSDEPTHCAMERA_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/CameraInfo.h>
#include <sensor_msgs/PointCloud2.h>


namespace AlleyHoopROSSensors
{
    //* A ros depth camera implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve point cloud data
    */
   
    class DepthCamera : public AlleyHoopMVC::Sensor
    {
        public:      
            /*!
            * \brief The constructor for the depth camera class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _point_cloud_topic the topic to retrieve pcl data from
            * \param _camera_info_topic the topic holding information about the camera
            */
            DepthCamera(std::string _name, ros::NodeHandle* _nh, std::string _point_cloud_topic, std::string _camera_info_topic);

            /*!
            * \brief The default destructor
            */
            virtual ~DepthCamera() = default;

            /*!
            * \brief this function is called when camera info can retrieved and generally happens only once
            * \param msg the message retrieved from ros
            */
            void cameraInfoCallBack(const sensor_msgs::CameraInfo& msg);

            /*!
            * \brief this function is called when there is new depth data available
            * \param msg the message retrieved from ros holding the depth data
            */
            void pointCloudCallBack(const sensor_msgs::PointCloud2& msg);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief get the current depth data
            */
            sensor_msgs::PointCloud2 getData();

            const std::string camera_info_topic_name; /**< the topic on which the depth camera info is published */
            const std::string point_cloud_topic_name; /**< the topic on which the point cloud data of the camera is published */

        protected:
            ros::Subscriber cam_info_sub; /**< the subscriber for camera info */
            ros::Subscriber pcl_sub; /**< the subscriber for point cloud data */
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            sensor_msgs::PointCloud2 currentPcl; /**< the most recent retrieved depth data */
    };

}

#endif //! ALLEYHOOPROSDEPTHCAMERA_H_