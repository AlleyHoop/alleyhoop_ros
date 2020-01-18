#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"

int main(int argc, char **argv)
{
    //setup ros
    ros::init(argc, argv, "alleyhoop_master");
    ros::NodeHandle nodeHandle;

    //ensure ros is running
    if (!ros::ok())
    {
        return 0;
    }

    //setup params
    std::string verbose_param = "none";
    if(nodeHandle.getParam("Alleyhoop_VerboseMode",verbose_param))
        if(verbose_param == "log")
        {
            AlleyHoopROSCore::Vehicle::verboseMode = true;
            AlleyHoopROSCore::Controller::verboseMode = true;
            AlleyHoopROSCore::FeatureFinder::verboseMode = true;
        }

    //setup core
    AlleyHoopMVC::Vehicle* vehicle = new AlleyHoopROSCore::Vehicle(&nodeHandle);
    AlleyHoopMVC::Controller* controller = new AlleyHoopROSCore::Controller(&nodeHandle, vehicle);

    //start routine
    bool state = true;
    while(state)
    {
        state = true;
        if(!controller->update()) state = false;
        if(!vehicle->update()) state = false;
    }

    //clean up
    delete controller;
    delete vehicle;
    return 0;
}
