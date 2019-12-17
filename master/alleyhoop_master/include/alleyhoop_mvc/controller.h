#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include <map>
#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_mvc/sensor.h"

namespace AlleyHoopMVC
{
    class Controller
    {
        public:
            virtual bool update() = 0;
            ~Controller()
            {
                for (std::map<std::string, Sensor*>::iterator it = sensors.begin(); it != sensors.end(); it++)
                {
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
                    sensors.insert({s->name, s});
                    return true;
                }
                return false;
            };
            bool removeSensor(std::string n)
            {
                if(sensors.find(n) != sensors.end())
                {
                    sensors.erase(n);
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
