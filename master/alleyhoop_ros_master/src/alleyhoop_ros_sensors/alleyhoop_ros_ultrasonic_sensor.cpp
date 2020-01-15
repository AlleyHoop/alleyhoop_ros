#include "alleyhoop_ros_sensors/alleyhoop_ros_ultrasonic_sensor.h"

namespace AlleyHoopROSSensors
{
    UltrasonicSensor::UltrasonicSensor(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), topic_name(_topic), distance(0)
    {
        sub = nh.subscribe(topic_name, 1, &UltrasonicSensor::callBack, this);
    }

    void UltrasonicSensor::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    int UltrasonicSensor::getData()
    {
        return distance;
    }

    void UltrasonicSensor::callBack(const std_msgs::UInt8 msg)
    {
        distance = msg.data;
    }
}