#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <map>
#include "alleyhoop_mvc/actuator.h"

namespace AutonomousDriving
{

    class Vehicle
    {
        public:
            virtual ~Vehicle() = default;
            virtual bool update() = 0;

	    protected:
	        Vehicle() {};

            std::map<std::string, Actuator*> actuators;
    };

}

#endif //! VEHICLE_H_
