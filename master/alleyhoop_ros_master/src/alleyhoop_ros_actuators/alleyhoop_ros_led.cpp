#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"


namespace AlleyHoopROSActuators
{
    uint64_t Led::timeMillis() 
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }


    Led::Led(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Actuator(_name), nh(*_nh), topic_name(_topic), state(false), pub_rate(250), pub_time(timeMillis() + pub_rate)
    {
        pub = nh.advertise<std_msgs::Bool>(topic_name, 1);
    }

    bool Led::getState()
    {
        return state;
    }

    void Led::setState(bool s)
    {
        state = s;
    }

    void Led::update()
    {
        if(timeMillis() > pub_time)
        {
            std_msgs::Bool msg;
            msg.data = state;
            pub.publish(msg);
            pub_time = timeMillis() + pub_rate;
        }
    }
}