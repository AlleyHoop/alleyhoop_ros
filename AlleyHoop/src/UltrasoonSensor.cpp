#include "../include/UltrasoonSensor.h"

namespace ControllableVehicle
{
    UltrasoonSensor::UltrasoonSensor(std::string _name)
        : Actuator(_name)
    {

    }

    UltrasoonSensor::~UltrasoonSensor()
    {
        
    }

    SerialMessaging::Data* UltrasoonSensor::getData()
    {

        return nullptr;
    }

}