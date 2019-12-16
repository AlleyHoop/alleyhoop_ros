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

            bool addActuator(Actuator* s) 
            {
                if(actuators.find(s->name) == actuators.end())
                {
                    actuators.insert({s->name, s});
                    return true;
                }
                return false;
            };
            bool removeActuator(std::string n)
            {
                if(actuators.find(n) != actuators.end())
                {
                    actuators.erase(n);
                    return true;
                }
                return false;
            };
            Actuator* getActuator(std::string n)
            {
                if(actuators.find(n) == actuators.end())
                {
                    return nullptr;
                }
                return actuators.find(n)->second;
            };

	    protected:
	        Vehicle() {};
            std::map<std::string, Actuator*> actuators;
    };

}

#endif //! VEHICLE_H_
