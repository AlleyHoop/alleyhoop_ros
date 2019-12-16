#include "alleyhoop_controller.h"
#include <sstream>
#include <iostream>

namespace AutonomousDriving
{

    AlleyHoopController::AlleyHoopController(int argc, char **argv)
    {
        ros::init(argc, argv, "alleyhoop_core"); 
    }

    void AlleyHoopController::update()
    {
        if (ros::ok())
        {
            // print text
            std::stringstream ss;
            ss << "vehicle starting..";
            ROS_INFO("%s", ss.str().c_str());
            ros::spinOnce();
        }
        else
        {
            std::cout << "ros was not running!" << std::endl;
        }
        
    }

}