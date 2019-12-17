#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "std_msgs/Bool.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROSActuators
{

    AlleyHoopLed::AlleyHoopLed(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Actuator(_name), nh(*_nh), topic_name(_topic), state(false)
    {
        pub = nh.advertise<std_msgs::Bool>(topic_name, 1000);
    }

    bool AlleyHoopLed::getState()
    {
        return state;
    }

    void AlleyHoopLed::setState(bool s)
    {
        state = s;
    }

    void AlleyHoopLed::update()
    {
        std_msgs::Bool msg;
        msg.data = state;
        pub.publish(msg);
    }

}