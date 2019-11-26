#include <iostream>
#include "./include/SerialCommunication.h"
#include "./include/LedData.h"


int main(int argc, const char** argv) {
    std::cout << "this is alley hoop's software architecture" << std::endl;
    
    SerialMessaging::SerialCommunication serCom = SerialMessaging::SerialCommunication("/dev/ttyACM0",9600);
    SerialMessaging::Data* ledData = new SerialMessaging::LedData();
    serCom.send(ledData);
    return 0;
}