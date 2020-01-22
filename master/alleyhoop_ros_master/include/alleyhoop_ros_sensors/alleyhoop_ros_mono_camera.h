#ifndef ALLEYHOOPROSMONOCAMERA_H_
#define ALLEYHOOPROSMONOCAMERA_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>


namespace AlleyHoopROSSensors
{
    //* A ros mono camera implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve image data
    */

    class MonoCamera : public AlleyHoopMVC::Sensor
    {
        
        public:     
            /*!
            * \brief The constructor for the camera class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _image_topic the topic to retrieve image data from
            * \param _camera_info_topic the topic holding information about the camera
            */ 
            MonoCamera(std::string _name, ros::NodeHandle* _nh, std::string _image_topic, std::string _camera_info_topic);

            /*!
            * \brief The default destructor
            */
            virtual ~MonoCamera() = default;

            /*!
            * \brief this function is called when there is new image data available
            * \param msg the message retrieved from ros holding the image data
            */
            void imageCallBack(const sensor_msgs::ImageConstPtr& msg);

            /*!
            * \brief this function is called when camera info can retrieved and generally happens only once
            * \param msg the message retrieved from ros
            */
            void cameraInfoCallBack(const sensor_msgs::CameraInfo& msg);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief get the current image data
            */
            cv_bridge::CvImagePtr getData();


            const std::string image_topic_name; /**< the topic on which the image data of the camera is published */
            const std::string camera_info_topic_name; /**< the topic on which the camera info is published */

        protected:
            ros::Subscriber image_sub;  /**< the subscriber for image data */
            ros::Subscriber cam_info_sub; /**< the subscriber for camera info */
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            cv_bridge::CvImagePtr currentImagePtr; /**< the most recent retrieved image */
    };

}

#endif //! ALLEYHOOPROSMONOCAMERA_H_