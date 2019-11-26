#ifndef ULTRASOONDATA_H_
#define ULTRASOONDATA_H_

#include "../include/Data.h"

namespace ControllableVehicle
{

class UltrasoonData : public SerialMessaging::Data
{
    public:
        UltrasoonData();
        ~UltrasoonData();

        void serialize();
        void unserialize();
};

};


#endif // ! ULTRASOONDATA_H_