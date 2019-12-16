#include "alleyhoop_master/alleyhoop_controller.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "alleyhoop_core");
    ros::NodeHandle n;
    AutonomousDriving::Controller* controller = new AutonomousDriving::AlleyHoopController(&n);

    while(true)
    {
        controller->update();
    }

    delete controller;
    return 0;
}
