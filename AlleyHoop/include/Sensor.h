#ifndef SENSOR_H_
#define SENSOR_H_

#include "./Data.h"

namespace ControllableVehicle
{

class Sensor
{
    public:
        virtual ~Sensor();
        virtual SerialMessaging::Data* getData() = 0;

        std::string name;

    protected: 
        Sensor(std::string _name);

};

};


#endif // ! SENSOR_H_