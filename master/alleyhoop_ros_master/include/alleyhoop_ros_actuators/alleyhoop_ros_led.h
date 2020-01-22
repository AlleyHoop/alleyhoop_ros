#ifndef ALLEYHOOPROSLED_H_
#define ALLEYHOOPROSLED_H_



#include <ros/ros.h>

#include "alleyhoop_mvc/actuator.h"

#include <chrono>
#include <cstdint>
#include <std_msgs/Bool.h>

namespace AlleyHoopROSActuators
{   
    //* A led implmentation of the actuator class from the alleyhoop_master package
    /**
    * A class that publishes data for a led
    *
    */
   
    class Led : public AlleyHoopMVC::Actuator
    {
        public: 
            /*!
            * \brief The constructor for the led class
            * \param _name the name of the actuator, is required to create the actuator base class
            * \param _nh the nodehandle to publish data on
            * \param _topic the topic on which data is to be published
            */     
            Led(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            /*!
            * \brief default destructor
            */
            virtual ~Led() = default;

            /*!
            * \brief set the state of the led
            * \param s a bool, the state to set the led
            */
            void setState(bool s);
            /*!
            * \brief get the current state of the led
            */
            bool getState();
            /*!
            * \brief update function, should be called from the base controller class
            */
            void update();
            /*!
            * \brief get the current time in milli seconds
            */
            static uint64_t timeMillis();


            const std::string topic_name; /**< the topic to publish led data on */

        protected:
            ros::Publisher pub; /**< the publisher */
            ros::NodeHandle nh; /**< the nodehandle*/

        private:
            bool state;     /**< the state of the led*/
            double pub_rate; /**< the rate with which the led state is published*/
            double pub_time; /**< the time the next state needs to be published */
            
    };

}

#endif //! ALLEYHOOPROSLED_H_