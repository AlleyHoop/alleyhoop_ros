#ifndef ULTRASOONSENSOR_H_
#define ULTRASOONSENSOR_H_

#include "../include/Actuator.h"

namespace ControllableVehicle
{

class UltrasoonSensor : public Actuator
{
    public:
        UltrasoonSensor(std::string _name);
        ~UltrasoonSensor();

        SerialMessaging::Data* getData();
};

};


#endif // ! ULTRASOONSENSOR_H_