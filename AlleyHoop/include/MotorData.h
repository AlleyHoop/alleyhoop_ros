#ifndef MOTORDATA_H_
#define MOTORDATA_H_

#include "../include/Data.h"

namespace ControllableVehicle
{

class MotorData : public SerialMessaging::Data
{
    public:
        MotorData();
        ~MotorData();

        void serialize();
        void unserialize();
};

};


#endif // ! MOTORDATA_H_