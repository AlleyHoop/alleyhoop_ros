#ifndef ALLEYHOOPROSMOTOR_H_
#define ALLEYHOOPROSMOTOR_H_



#include <ros/ros.h>

#include "alleyhoop_mvc/actuator.h"
#include <chrono>
#include <cstdint>
#include <std_msgs/Int16.h>

namespace AlleyHoopROSActuators
{
    //* A motor implementation of the actuator class from the alleyhoop_master package
    /**
    * A class that publishes data for a motor
    *
    */
   
    class Motor : public AlleyHoopMVC::Actuator
    {
        public:    
            /*!
            * \brief The constructor for the motor class
            * \param _name the name of the actuator, is required to create the actuator base class
            * \param _nh the nodehandle to publish data on
            * \param _topic the topic on which data is to be published
            */   
            Motor(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            /*!
            * \brief default destructor
            */
            virtual ~Motor() = default;

            /*!
            * \brief set the state of the motor
            * \param d an integer, the state to set the motor to
            */
            void setData(int d);

            /*!
            * \brief get the current state of the motor
            */
            int getData();

            /*!
            * \brief update function, should be called from the base controller class
            */
            void update();

            /*!
            * \brief get the current time in milli seconds
            */
            static uint64_t timeMillis();

            
            const std::string topic_name; /**< the topic to publish motor data on */

        protected:
            ros::Publisher pub; /**< the publisher */
            ros::NodeHandle nh; /**< the nodehandle*/

        private:
            int data; /**< the state of the motor*/
            double pub_rate; /**< the rate with which the motor state is published in milli seconds*/
            double pub_time; /**< the time the next state needs to be published in milli seconds since epoch*/

            
    };

}

#endif //! ALLEYHOOPROSMOTOR_H_