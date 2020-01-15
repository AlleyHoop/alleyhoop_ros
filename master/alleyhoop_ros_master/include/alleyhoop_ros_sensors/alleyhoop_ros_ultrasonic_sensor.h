#ifndef ALLEYHOOPROSULTRASOON_H_
#define ALLEYHOOPROSULTRASOON_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <std_msgs/UInt8.h>



namespace AlleyHoopROSSensors
{

    class UltrasonicSensor : public AlleyHoopMVC::Sensor
    {
        public:      
            UltrasonicSensor(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            virtual ~UltrasonicSensor() = default;

            void callBack(const std_msgs::UInt8 msg);
            void update();
            int getData();

            const std::string topic_name;

        protected:
            ros::Subscriber sub;
            ros::NodeHandle nh;

        private:
            int distance;
    };

}

#endif //! ALLEYHOOPROSULTRASOON_H_