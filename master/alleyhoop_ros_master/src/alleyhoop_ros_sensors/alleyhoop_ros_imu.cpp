#include "alleyhoop_ros_sensors/alleyhoop_ros_imu.h"

namespace AlleyHoopROSSensors
{
    Imu::Imu(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), topic_name(_topic)
    {
        sub = nh.subscribe(topic_name, 1, &Imu::callBack, this);
    }

    void Imu::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    void Imu::getData()
    {
        
    }

    void Imu::callBack(const sensor_msgs::Imu& msg)
    {
        
    }
}