#ifndef LED_H_
#define LED_H_

#include "./Actuator.h"

namespace ControllableVehicle
{

class Led : public Actuator
{
    public:
        Led(std::string _name);
        ~Led();

        SerialMessaging::Data* getData();

};

};


#endif // ! LED_H_