#ifndef ALLEYHOOPROSMONOCAMERA_H_
#define ALLEYHOOPROSMONOCAMERA_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>


namespace AlleyHoopROSSensors
{

    class MonoCamera : public AlleyHoopMVC::Sensor
    {
        public:      
            MonoCamera(std::string _name, ros::NodeHandle* _nh, std::string _image_topic, std::string _camera_info_topic);
            virtual ~MonoCamera() = default;

            void callBack(const sensor_msgs::ImageConstPtr& msg);
            void update();
            cv_bridge::CvImagePtr getData();

            const std::string image_topic_name;
            const std::string camera_info_topic_name;

        protected:
            ros::Subscriber sub;
            ros::NodeHandle nh;

        private:
            cv_bridge::CvImagePtr currentImagePtr;
    };

}

#endif //! ALLEYHOOPROSMONOCAMERA_H_