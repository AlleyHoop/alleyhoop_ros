#include "alleyhoop_ros_actuators/alleyhoop_ros_led.h"
#include "std_msgs/Bool.h"


namespace AlleyHoopROSActuators
{
    uint64_t AlleyHoopLed::timeMillis() 
    {
        using namespace std::chrono;
        return duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
    }


    AlleyHoopLed::AlleyHoopLed(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Actuator(_name), nh(*_nh), topic_name(_topic), state(false), pub_rate(250), pub_time(timeMillis() + pub_rate)
    {
        pub = nh.advertise<std_msgs::Bool>(topic_name, 1);
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
        if(timeMillis() > pub_time)
        {
            std_msgs::Bool msg;
            msg.data = state;
            pub.publish(msg);
            pub_time = timeMillis() + pub_rate;
        }
    }
}