#ifndef ALLEYHOOPROSLED_H_
#define ALLEYHOOPROSLED_H_

#include "alleyhoop_mvc/actuator.h"
#include "ros/ros.h"


namespace AlleyHoopROSActuators
{

    class AlleyHoopLed : public AlleyHoopMVC::Actuator
    {
        public:      
            AlleyHoopLed(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            virtual ~AlleyHoopLed() = default;

            void setState(bool s);
            bool getState();
            void update();

            const std::string topic_name;

        protected:
            ros::Publisher pub;
            ros::NodeHandle nh;

        private:
            bool state;
    };

}

#endif //! ALLEYHOOPROSLED_H_