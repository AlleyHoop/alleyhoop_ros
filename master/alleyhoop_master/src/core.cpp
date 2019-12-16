#include "alleyhoop_master/alleyhoop_controller.h"
#include "alleyhoop_master/alleyhoop_vehicle.h"
#include "alleyhoop_master/alleyhoop_feature_finder.h"

int main(int argc, char **argv)
{
    ros::init(argc, argv, "alleyhoop_master");
    ros::NodeHandle n;

    AutonomousDriving::Controller* controller = new AutonomousDriving::AlleyHoopController(&n);
    AutonomousDriving::Vehicle* vehicle = new AutonomousDriving::AlleyHoopVehicle(&n);
    AutonomousDriving::Model* model = new AutonomousDriving::AlleyHoopFeatureFinder(&n);

    while(true)
    {
        controller->update();
        vehicle->update();
        model->update();
    }

    delete controller;
    delete vehicle;
    delete model;
    return 0;
}
