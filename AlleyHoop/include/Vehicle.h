#ifndef VEHICLE_H_
#define VEHICLE_H_

#include <string>
#include <map>
#include <list>

#include "./Sensor.h"
#include "./Actuator.h"
#include "./SerialCommunication.h"

namespace ControllableVehicle
{
    
class Vehicle
{
    public:
        Vehicle();
        ~Vehicle() = default;
        std::string name;

        void run();
    
    private:
        std::map<std::string, Sensor> sensors;
        std::map<std::string, Actuator> actuators;
        std::list<SerialMessaging::SerialCommunication> serialComs;
};

};


#endif // ! VEHICLE_H_