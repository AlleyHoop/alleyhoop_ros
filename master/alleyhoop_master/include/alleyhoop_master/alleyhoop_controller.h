#ifndef ALLEYHOOPCONTROLLER_H_
#define ALLEYHOOPCONTROLLER_H_

#include "alleyhoop_master/controller.h"
#include "ros/ros.h"


namespace AutonomousDriving
{
    class AlleyHoopController : public Controller
    {
        public:
            AlleyHoopController(ros::NodeHandle* _nh, Vehicle* v);
            ~AlleyHoopController() = default;
            void update();

        private:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //! ALLEYHOOPCONTROLLER_H_
