#include "../include/LedData.h"

namespace ControllableVehicle
{

    LedData::LedData()
        : SerialMessaging::Data("LedData"), led_nr(0), status(true)
    {

    }

    LedData::~LedData()
    {

    }

    void LedData::serialize()
    {
        if(status)
        {
            char* m = "true"; 
            message = m;
        }
        else
        {
            char* m = "false";
            message = m;
        }
        
    }

    void LedData::unserialize()
    {

    }
}