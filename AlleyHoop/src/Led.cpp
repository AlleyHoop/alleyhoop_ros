#include "../include/Led.h"

namespace ControllableVehicle
{
    Led::Led(std::string _name)
        : Actuator(_name)
    {

    }

    Led::~Led()
    {
        
    }

    SerialMessaging::Data* Led::getData()
    {

        return nullptr;
    }

}