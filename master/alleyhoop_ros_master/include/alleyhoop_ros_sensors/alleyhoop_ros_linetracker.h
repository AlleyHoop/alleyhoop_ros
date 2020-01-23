#ifndef ALLEYHOOPROSLINETRACKER_H_
#define ALLEYHOOPROSLINETRACKER_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <std_msgs/Bool.h>


namespace AlleyHoopROSSensors
{
    //* A ros LineTracker sensor implementation of the sensor class from the alleyhoop_master package
    /**
    * This sensor class is used to retrieve LineTracker sensor data
    */

    class LineTracker : public AlleyHoopMVC::Sensor
    {
        public:     
            /*!
            * \brief The constructor for the LineTracker sensor class
            * \param _name the name of the sensor, required by the base sensor class
            * \param _nh the nodehandle to publish data on
            * \param _topic the topic to retrieve LineTracker sensor data from
            */  
            LineTracker(std::string _name, ros::NodeHandle* _nh, std::string _topic);

            /*!
            * \brief The default destructor
            */
            virtual ~LineTracker() = default;

            /*!
            * \brief this function is called when new LineTracker sensor data is available
            * \param scan the message retrieved from ros
            */
            void callBack(const std_msgs::Bool msg);

            /*!
            * \brief this function should be called from the base controller class
            */
            void update();

            /*!
            * \brief function to retrieve data
            */
            bool getData();

            const std::string topic_name; /**< the topic on which the LineTracker sensor data is published */

        protected:
            ros::Subscriber sub; /**< the subscriber for laser data */
            ros::NodeHandle nh; /**< the nodehandle */

        private:
            bool state; /**< the state of the tracker */
    };

}

#endif //! ALLEYHOOPROSLINETRACKER_H_