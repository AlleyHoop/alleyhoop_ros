#include "alleyhoop_ros_actuators/alleyhoop_ros_motor.h"


namespace AlleyHoopROSActuators
{
    uint64_t Motor::timeMillis() 
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }


    Motor::Motor(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Actuator(_name), nh(*_nh), topic_name(_topic), percentage(50), pub_rate(250), pub_time(timeMillis() + pub_rate)
    {
        pub = nh.advertise<std_msgs::UInt8>(topic_name, 1);
    }

    int Motor::getPercentage()
    {
        return percentage;
    }

    void Motor::setPercentage(int p)
    {
        percentage = p;
    }

    void Motor::update()
    {
        if(timeMillis() > pub_time)
        {
            std_msgs::UInt8 msg;
            msg.data = percentage;
            pub.publish(msg);
            pub_time = timeMillis() + pub_rate;
        }
    }
}