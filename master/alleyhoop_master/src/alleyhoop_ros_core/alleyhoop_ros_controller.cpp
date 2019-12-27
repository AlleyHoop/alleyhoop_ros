#include "alleyhoop_ros_core/alleyhoop_ros_controller.h"
#include "alleyhoop_ros_core/alleyhoop_ros_vehicle.h"

#include <sstream>
#include <iostream>

namespace AlleyHoopROS
{

    AlleyHoopController::AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v)
	: AlleyHoopMVC::Controller(v), nh(*_nh), imageFeatureFinder(_nh)
    {
        //setup sensors, add to controller base class for life line managing and update routine
        ultrasoon_sensor = new AlleyHoopROSSensors::AlleyHoopUltrasoon("ultrasoon_sensor", _nh, "/arduino_slave/ultrasoon_sensor");
        addSensor(ultrasoon_sensor);

        mono_camera_1 = new AlleyHoopROSSensors::AlleyHoopMonoCamera("mono_camera_1", _nh, "/raspi_camera/image", "/raspi_camera/camera_info");
        addSensor(mono_camera_1);

        lidar1 = new AlleyHoopROSSensors::AlleyHoopLidar("lidar1", _nh, "/scan");
        addSensor(lidar1);
    }

    bool AlleyHoopController::update()
    {
        if (ros::ok())
        {
            // make decisions
            if(AlleyHoopROS::AlleyHoopVehicle* ah_vehicle = dynamic_cast<AlleyHoopROS::AlleyHoopVehicle*>(vehicle))
            {
                int ultrasoon_data = ultrasoon_sensor->getData();
                if(ultrasoon_data < 30 && ultrasoon_data > 0)
                {
                    ah_vehicle->led1->setState(true);
                }
                else
                {
                    ah_vehicle->led1->setState(false);
                }
            }

            //update routinely
            updateSensors(); //used for conventional implementation // for ros the following line, 'spinOnce()' is called instead 
            ros::spinOnce();
            return true;
        }

        std::cout << "program terminated" << std::endl;
        return false;
    }

}
