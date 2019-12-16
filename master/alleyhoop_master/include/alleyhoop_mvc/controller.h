#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "alleyhoop_master/vehicle.h"

namespace AutonomousDriving
{
    class Controller
    {
        public:
            virtual ~Controller() = default;
            virtual bool update() = 0;

	    protected:
	        Controller(Vehicle* v) : vehicle(v)  {};
            Vehicle* vehicle;
    };
}

#endif //! CONTROLLER_H_
