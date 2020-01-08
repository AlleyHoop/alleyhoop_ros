#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <map>
#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_mvc/sensor.h"
#include <iostream>

namespace AlleyHoopMVC
{
    class Controller
    {
        public:
            virtual bool update() = 0;
            virtual ~Controller()
            {
                for (std::map<std::string, Sensor*>::iterator it = sensors.begin(); it != sensors.end(); it++)
                {
                    std::cout << "deleted sensor " + it->second->name << std::endl;
                    delete it->second;
                }
            } 

            void updateSensors()
            {
                for (std::map<std::string, Sensor*>::iterator it = sensors.begin(); it != sensors.end(); it++)
                {
                    it->second->update();
                }
            }

            bool addSensor(Sensor* s) 
            {
                if(sensors.find(s->name) == sensors.end())
                {
                    std::cout << "added sensor " + s->name << std::endl;
                    sensors.insert({s->name, s});
                    return true;
                }
                return false;
            };
            bool removeSensor(std::string n)
            {
                if(sensors.find(n) != sensors.end())
                {
                    std::cout << "removed and deleted sensor " + n << std::endl;
                    Sensor* s = sensors.find(n)->second;
                    sensors.erase(n);
                    delete s;
                    return true;
                }
                return false;
            };
            Sensor* getSensor(std::string n)
            {
                if(sensors.find(n) == sensors.end())
                {
                    return nullptr;
                }
                return sensors.find(n)->second;
            };

	    protected:
	        Controller(Vehicle* v) : vehicle(v)  {};
            
            Vehicle* vehicle;
            std::map<std::string, Sensor*> sensors;
    };
}

#endif //! CONTROLLER_H_
