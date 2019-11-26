#ifndef SERIALCOMMUNICATION_H_
#define SERIALCOMMUNICATION_H_

#include <string>

/*
If on a raspi make sure to disable raspi-config -> serial communication and append 'enable_uart=1' in /boot/config.txt
*/

namespace SerialMessaging
{

class Data;

class SerialCommunication
{
    public:
        SerialCommunication(std::string _port, int _baudrate);
        ~SerialCommunication();

        void send(Data* data);
        void receive(Data* data);

        std::string port;
        int baudrate;

    private:
        int fd;
};

};

#endif // !SERIALCOMMUNICATION_H_