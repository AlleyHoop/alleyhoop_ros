#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros_core/alleyhoop_ros_feature_finder.h"

int main(int argc, char **argv)
{
    //setup ros
    ros::init(argc, argv, "alleyhoop_master");
    ros::NodeHandle nodeHandle;

    //setup core
    AlleyHoopMVC::Vehicle* vehicle = new AlleyHoopROSCore::Vehicle(&nodeHandle);
    AlleyHoopMVC::Controller* controller = new AlleyHoopROSCore::Controller(&nodeHandle, vehicle);

    //setup params
    std::string verbose_param = "none";
    if(nodeHandle.getParam("AlleyhoopVerboseMode",verbose_param))
        if(verbose_param == "display" || verbose_param == "full_verbose")
        {
            AlleyHoopROSCore::Vehicle::verboseDisplay = true;
            AlleyHoopROSCore::Controller::verboseDisplay = true;
            AlleyHoopROSCore::FeatureFinder::verboseDisplay = true;
        }
        if(verbose_param == "log" || verbose_param == "full_verbose")
        {
            AlleyHoopROSCore::Vehicle::verboseLog = true;
            AlleyHoopROSCore::Controller::verboseLog = true;
            AlleyHoopROSCore::FeatureFinder::verboseLog = true;
        }

    //start routine
    bool state = true;
    while(state)
    {
        state = true;
        if(!controller->update()) state = false;
        if(!vehicle->update()) state = false;
    }

    delete controller;
    delete vehicle;
    return 0;
}
