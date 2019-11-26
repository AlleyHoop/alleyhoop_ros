#include "../include/Motor.h"

namespace ControllableVehicle
{
    Motor::Motor(std::string _name)
        : Actuator(_name)
    {

    }

    Motor::~Motor()
    {
        
    }

    SerialMessaging::Data* Motor::getData()
    {

        return nullptr;
    }

}