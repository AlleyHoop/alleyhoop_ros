#ifndef ALLEYHOOPIMU_H_
#define ALLEYHOOPIMU_H_



#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/Imu.h>


namespace AlleyHoopROSSensors
{
    //* A ros interial measurement unit implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve imu data
    */

    class Imu : public AlleyHoopMVC::Sensor
    {
        public:      
            /*!
            * \brief The constructor for the imu sensor class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _topic the topic to retrieve imu data from such as accelaration, velocity and angular movement
            */
            Imu(std::string _name, ros::NodeHandle* _nh, std::string _topic);

            /*!
            * \brief The default destructor
            */
            virtual ~Imu() = default;

            /*!
            * \brief this function is called when new imu data is available
            * \param msg the message retrieved from ros
            */
            void callBack(const sensor_msgs::Imu& msg);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief get the current imu data
            * \todo does not yet return data. actually return the data as vectors
            */
            void getData();

            
            const std::string topic_name; /**< the topic on which the imu data is published */

        protected:
            ros::Subscriber sub; /**< the subscriber for imu data */
            ros::NodeHandle nh; /**< the nodehandle */
    };

}

#endif //! ALLEYHOOPIMU_H_