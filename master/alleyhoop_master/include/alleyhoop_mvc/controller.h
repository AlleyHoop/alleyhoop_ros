#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <map>
#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_mvc/sensor.h"

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
            std::map<std::string, Sensor*> sensors;
    };
}

#endif //! CONTROLLER_H_
