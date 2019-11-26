#include "../include/SerialCommunication.h"
#include "../include/Data.h"
#include <wiringPi.h>
#include <wiringSerial.h>
#include <iostream>

namespace SerialMessaging
{
    SerialCommunication::SerialCommunication(std::string _port, int _baudrate)
        : port(_port), baudrate(_baudrate), fd(-1)
    {
        fd = serialOpen(port.c_str(),baudrate);

        if(wiringPiSetup() < 0)
        {
            std::cout << "failed setting up wiring pi" << std::endl;
        }

        if(fd < 0)
        {
            std::cout << "Unable to open serial device:" << port << std::endl;
        }
    }

    SerialCommunication::~SerialCommunication()
    {
            serialClose(fd);
    }

    void SerialCommunication::send(Data* data)
    {
        if(fd > 0)
        {
            data->serialize();
             std::cout << "sending data : " << data->message << std::endl;
            serialPrintf(fd, data->message);
        }
        else
        {
             std::cout << "device :" << port << " not available" << std::endl;
        }
    }

    void SerialCommunication::receive(Data* data)
    {
        //if(fd > 0)
        //    if(serialDataAvail(fd) > 0)
        //        data->getMessage() = serialGetchar(fd);
    }

}
