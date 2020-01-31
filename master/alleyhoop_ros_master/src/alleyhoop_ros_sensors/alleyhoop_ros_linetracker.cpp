#include "alleyhoop_ros_sensors/alleyhoop_ros_linetracker.h"

namespace AlleyHoopROSSensors
{
    LineTracker::LineTracker(std::string _name, ros::NodeHandle* _nh, std::string _topic)
	    : AlleyHoopMVC::Sensor(_name), nh(*_nh), topic_name(_topic), value(0)
    {
        sub = nh.subscribe(topic_name, 1, &LineTracker::callBack, this);
    }

    void LineTracker::update()
    {
        //nothing for ros sensor // rosspin() is called from the controller
    }

    int LineTracker::getData()
    {
        return value;
    }

    void LineTracker::callBack(const std_msgs::UInt8 msg)
    {
        value = msg.data;
    }
}