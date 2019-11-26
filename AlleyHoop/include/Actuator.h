#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <string>
#include "./Data.h"

namespace ControllableVehicle
{

class Actuator
{
    public:
        virtual ~Actuator();
        virtual SerialMessaging::Data* getData() = 0;

        std::string name;

    protected: 
        Actuator(std::string _name);

};


};


#endif // ! ACTUATOR_H_