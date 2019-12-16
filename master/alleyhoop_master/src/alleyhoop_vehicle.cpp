#include "alleyhoop_master/alleyhoop_vehicle.h"
#include <sstream>
#include <iostream>

namespace AutonomousDriving
{

    AlleyHoopVehicle:AlleyHoopVehicle(ros::NodeHandle* _nh)
	: Vehicle(), nh(*_nh)
    {
    }

    void AlleyHoopVehicle::update()
    {
        if (ros::ok())
        {
            // print text
            std::stringstream ss;
            ss << "vehicle running...";
            ROS_INFO("%s", ss.str().c_str());
            ros::spinOnce();
        }
        else
        {
            std::cout << "ros was not running!" << std::endl;
        }
    }

}