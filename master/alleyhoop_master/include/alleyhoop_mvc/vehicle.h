#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <map>
#include "alleyhoop_mvc/actuator.h"

namespace AlleyHoopMVC
{

    class Vehicle
    {
        public:
            virtual bool update() = 0;

            virtual ~Vehicle()
            {
                for (std::map<std::string, Actuator*>::iterator it = actuators.begin(); it != actuators.end(); it++)
                {
                    std::cout << "deleted actuator " + it->second->name << std::endl;
                    delete it->second;
                }
            }

            void updateActuators()
            {
                for (std::map<std::string, Actuator*>::iterator it = actuators.begin(); it != actuators.end(); it++)
                {
                    it->second->update();
                }
            }

            bool addActuator(Actuator* s) 
            {
                if(actuators.find(s->name) == actuators.end())
                {
                    std::cout << "added actuator " + s->name << std::endl;
                    actuators.insert({s->name, s});
                    return true;
                }
                return false;
            };
            bool removeActuator(std::string n)
            {
                if(actuators.find(n) != actuators.end())
                {
                    std::cout << "removed and deleted actuator " + n << std::endl;
                    Actuator* s = actuators.find(n)->second;
                    actuators.erase(n);
                    delete s;
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
