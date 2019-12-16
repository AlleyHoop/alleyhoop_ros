#ifndef ALLEYHOOPCONTROLLER_H_
#define ALLEYHOOPCONTROLLER_H_

#include "controller.h"
#include "ros/ros.h"


namespace AutonomousDriving
{

    class AlleyHoopController : public Controller
    {
        public:
            AlleyHoopController(int argc, char **argv);
            ~AlleyHoopController() = default;
            void update();

        private:
            //ros
            ros::NodeHandle n;
    };

}

#endif //! ALLEYHOOPCONTROLLER_H_