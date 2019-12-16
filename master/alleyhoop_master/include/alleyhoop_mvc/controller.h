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
