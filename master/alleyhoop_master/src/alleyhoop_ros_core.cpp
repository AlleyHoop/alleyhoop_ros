#include "alleyhoop_ros/alleyhoop_ros_controller.h"
#include "alleyhoop_ros/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros/alleyhoop_ros_feature_finder.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "alleyhoop_master");
    ros::NodeHandle n;

    AutonomousDriving::Vehicle* vehicle = new AlleyHoopAutonomousDriving::AlleyHoopVehicle(&n);
    AutonomousDriving::Controller* controller = new AlleyHoopAutonomousDriving::AlleyHoopController(&n, vehicle);
    AutonomousDriving::Model* model = new AlleyHoopAutonomousDriving::AlleyHoopFeatureFinder(&n);

    bool state = true;
    while(state)
    {
        state = true;
        if(!controller->update()) state = false;
        if(!vehicle->update()) state = false;
    }

    delete controller;
    delete vehicle;
    delete model;
    return 0;
}
