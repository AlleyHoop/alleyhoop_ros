#ifndef ALLEYHOOPROSLIDAR_H_
#define ALLEYHOOPROSLIDAR_H_

#include <ros/ros.h>

#include "alleyhoop_mvc/sensor.h"

#include <sensor_msgs/LaserScan.h>

#define RAD2DEG(x) ((x)*180./M_PI)

namespace AlleyHoopROSSensors
{
    class AlleyHoopLidar : public AlleyHoopMVC::Sensor
    {
        public:      
            AlleyHoopLidar(std::string _name, ros::NodeHandle* _nh, std::string _laser_scan_topic);
            virtual ~AlleyHoopLidar() = default;

            void callBack(const sensor_msgs::LaserScan::ConstPtr& scan);
            void update();
            void getData();

            const std::string laser_scan_topic_name;

        protected:
            ros::Subscriber sub;
            ros::NodeHandle nh;

        //TODO add a variable for saving scans nad implement getdata
    };

}

#endif //! ALLEYHOOPROSLIDAR_H_