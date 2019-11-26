#ifndef LEDDATA_H_
#define LEDDATA_H_

#include "./Data.h"

namespace ControllableVehicle
{

class LedData : public SerialMessaging::Data
{
    public:
        LedData();
        ~LedData();
        void serialize();
        void unserialize();

        bool status;
        int led_nr;
};

};


#endif // ! LEDDATA_H_