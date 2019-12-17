#ifndef ALLEYHOOPROSULTRASOON_H_
#define ALLEYHOOPROSULTRASOON_H_

#include "alleyhoop_mvc/sensor.h"
#include "std_msgs/UInt8.h"
#include "ros/ros.h"


namespace AlleyHoopROSSensors
{

    class AlleyHoopUltrasoon : public AlleyHoopMVC::Sensor
    {
        public:      
            AlleyHoopUltrasoon(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            virtual ~AlleyHoopUltrasoon() = default;

            void callBack(const std_msgs::UInt8 msg);

            const std::string topic_name;

        protected:
            ros::Subscriber sub;
            ros::NodeHandle nh;

        private:
            int distance;
    };

}

#endif //! ALLEYHOOPROSULTRASOON_H_