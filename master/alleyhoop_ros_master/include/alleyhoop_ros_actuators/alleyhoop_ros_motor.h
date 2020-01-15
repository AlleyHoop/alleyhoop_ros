#ifndef ALLEYHOOPROSMOTOR_H_
#define ALLEYHOOPROSMOTOR_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/actuator.h"
#include <chrono>
#include <cstdint>
#include <std_msgs/UInt8.h>

namespace AlleyHoopROSActuators
{

    class Motor : public AlleyHoopMVC::Actuator
    {
        public:      
            Motor(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            virtual ~Motor() = default;

            void setPercentage(int p);
            int getPercentage();
            void update();

            static uint64_t timeMillis();

            const std::string topic_name;

        protected:
            ros::Publisher pub;
            ros::NodeHandle nh;

        private:
            int percentage;
            double pub_rate;
            double pub_time;

            
    };

}

#endif //! ALLEYHOOPROSMOTOR_H_