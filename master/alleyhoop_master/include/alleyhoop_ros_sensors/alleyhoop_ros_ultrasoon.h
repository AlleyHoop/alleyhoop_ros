#ifndef ALLEYHOOPROSULTRASOON_H_
#define ALLEYHOOPROSULTRASOON_H_

#include "alleyhoop_ros/alleyhoop_ros_sensor.h"
#include "std_msgs/String.h"
#include "ros/ros.h"


namespace AlleyHoopROSSensors
{

    class AlleyHoopUltrasoon : public AlleyHoopROS::AlleyHoopSensor
    {
        public:      
            ~AlleyHoopUltrasoon() = default;
            void sensorDataCallBack();

        private:
            AlleyHoopUltrasoon(ros::NodeHandle* _nh, std::string _name, std::string _topic);
    };

}

#endif //! ALLEYHOOPROSULTRASOON_H_