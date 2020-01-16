#ifndef ALLEYHOOPIMU_H_
#define ALLEYHOOPIMU_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/Imu.h>


namespace AlleyHoopROSSensors
{

    class Imu : public AlleyHoopMVC::Sensor
    {
        public:      
            Imu(std::string _name, ros::NodeHandle* _nh, std::string _topic);
            virtual ~Imu() = default;

            void callBack(const sensor_msgs::Imu& msg);
            void update();
            void getData();

            const std::string topic_name;

        protected:
            ros::Subscriber sub;
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPIMU_H_