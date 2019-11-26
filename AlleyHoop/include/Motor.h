#ifndef MOTOR_H_
#define MOTOR_H_

#include "../include/Actuator.h"

namespace ControllableVehicle
{

class Motor : public Actuator
{
    public:
        Motor(std::string _name);
        ~Motor() = default;

        SerialMessaging::Data* getData();
};

};


#endif // ! MOTOR_H_