#include "alleyhoop_ros/alleyhoop_ros_vehicle.h"
#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopVehicle::AlleyHoopVehicle(ros::NodeHandle* _nh)
	: AlleyHoopMVC::Vehicle(), nh(*_nh)
    {
        
    }

    bool AlleyHoopVehicle::update()
    {
        if (ros::ok())
        {
            // print text
            std::stringstream ss;
            ss << "vehicle running...";
            ROS_INFO("%s", ss.str().c_str());
            ros::spinOnce();
            return true;
        }

        std::cout << "roscore was not running!" << std::endl;
        return false;
    }

}