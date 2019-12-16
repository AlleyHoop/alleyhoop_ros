#ifndef  ALLEYHOOPROSCONTROLLER_H_
#define  ALLEYHOOPROSCONTROLLER_H_

#include "alleyhoop_mvc/controller.h"
#include "ros/ros.h"


namespace AlleyHoopROS
{
    class AlleyHoopController : public AlleyHoopMVC::Controller
    {
        public:
            AlleyHoopController(ros::NodeHandle* _nh, AlleyHoopMVC::Vehicle* v);
            ~AlleyHoopController() = default;
            bool update();

        protected:
            //ros
            ros::NodeHandle nh;
    };

}

#endif //!  ALLEYHOOPROSCONTROLLER_H_
