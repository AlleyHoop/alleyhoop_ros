#ifndef ALLEYHOOPCONTROLLER_H_
#define ALLEYHOOPCONTROLLER_H_

#include "alleyhoop_mvc/controller.h"
#include "ros/ros.h"


namespace AlleyHoopAutonomousDriving
{
    class AlleyHoopController : public AutonomousDriving::Controller
    {
        public:
            AlleyHoopController(ros::NodeHandle* _nh, Vehicle* v);
            ~AlleyHoopController() = default;
            bool update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPCONTROLLER_H_
