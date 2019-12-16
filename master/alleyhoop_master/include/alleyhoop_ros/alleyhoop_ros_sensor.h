#ifndef ALLEYHOOPROSSENSOR_H_
#define ALLEYHOOPROSSENSOR_H_

#include "alleyhoop_mvc/sensor.h"
#include "ros/ros.h"


namespace AlleyHoopROS
{

    class AlleyHoopSensor : public AlleyHoopMVC::Sensor
    {
        public:      
            ~AlleyHoopSensor() = default;
            virtual void sensorDataCallBack() = 0;

        protected:
            AlleyHoopSensor(ros::NodeHandle* _nh, std::string _name, std::string _topic)
                : AlleyHoopMVC::Sensor(_name), nh(*_nh) 
                {
                    sub = nh.subscribe(std::string("sensor_"+_name).c_str(), 1000, sensorDataCallBack);
                };
            ros::Subscriber sub;
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPROSSENSOR_H_