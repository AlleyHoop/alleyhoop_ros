#ifndef ALLEYHOOPROSULTRASOON_H_
#define ALLEYHOOPROSULTRASOON_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <std_msgs/UInt8.h>



namespace AlleyHoopROSSensors
{
    //* A ros ultrasonic sensor implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve ultrasonic sensor data
    */

    class UltrasonicSensor : public AlleyHoopMVC::Sensor
    {
        public:     
            /*!
            * \brief The constructor for the ultrasonic sensor class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _topic the topic to retrieve ultrasonic sensor data from
            */  
            UltrasonicSensor(std::string _name, ros::NodeHandle* _nh, std::string _topic);

            /*!
            * \brief The default destructor
            */
            virtual ~UltrasonicSensor() = default;

            /*!
            * \brief this function is called when new ultrasonic sensor data is available
            * \param scan the message retrieved from ros
            */
            void callBack(const std_msgs::UInt8 msg);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief function to retrieve data
            */
            int getData();

            const std::string topic_name; /**< the topic on which the ultrasonic sensor data is published */

        protected:
            ros::Subscriber sub; /**< the subscriber for laser data */
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            int distance;
    };

}

#endif //! ALLEYHOOPROSULTRASOON_H_