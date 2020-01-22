#ifndef ALLEYHOOPROSLIDAR_H_
#define ALLEYHOOPROSLIDAR_H_


#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/LaserScan.h>

#define RAD2DEG(x) ((x)*180./M_PI)


namespace AlleyHoopROSSensors
{
    //* A ros lidar implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve lidar data
    */

    class Lidar : public AlleyHoopMVC::Sensor
    {
        public:    
            /*!
            * \brief The constructor for the lidar sensor class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _laser_scan_topic the topic to retrieve lidar data from
            */  
            Lidar(std::string _name, ros::NodeHandle* _nh, std::string _laser_scan_topic);

            /*!
            * \brief The default destructor
            */
            virtual ~Lidar() = default;

            /*!
            * \brief this function is called when new lidar data is available
            * \param scan the message retrieved from ros
            */
            void callBack(const sensor_msgs::LaserScan::ConstPtr& scan);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief function to retrieve data
            * \TODO actually return data
            */
            void getData();

            const std::string laser_scan_topic_name; /**< the topic on which the laser scan data is published */

        protected:
            ros::Subscriber sub; /**< the subscriber for laser data */
            ros::NodeHandle nh; /**< the nodehandle */
    };

}

#endif //! ALLEYHOOPROSLIDAR_H_