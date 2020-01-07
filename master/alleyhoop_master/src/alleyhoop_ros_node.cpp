#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"
#include "alleyhoop_ros_core/alleyhoop_ros_image_feature_finder.h"

int main(int argc, char **argv)
{
    //setup ros
    ros::init(argc, argv, "alleyhoop_master");
    ros::NodeHandle nodeHandle;

    //setup core
    AlleyHoopMVC::Vehicle* vehicle = new AlleyHoopROS::AlleyHoopVehicle(&nodeHandle);
    AlleyHoopMVC::Controller* controller = new AlleyHoopROS::AlleyHoopController(&nodeHandle, vehicle);

    //setup params
    std::string verbose_param = "none";
    if(nodeHandle.getParam("AlleyhoopVerboseMode",verbose_param))
        if(verbose_param == "display" || verbose_param == "full_verbose")
        {
            AlleyHoopROS::AlleyHoopVehicle::verboseDisplay = true;
            AlleyHoopROS::AlleyHoopController::verboseDisplay = true;
            AlleyHoopROS::AlleyHoopImageFeatureFinder::verboseDisplay = true;
        }
        if(verbose_param == "log" || verbose_param == "full_verbose")
        {
            AlleyHoopROS::AlleyHoopVehicle::verboseLog = true;
            AlleyHoopROS::AlleyHoopController::verboseLog = true;
            AlleyHoopROS::AlleyHoopImageFeatureFinder::verboseLog = true;
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
