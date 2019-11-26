#ifndef DATA_H_
#define DATA_H_

#include <string>

namespace SerialMessaging
{

class Data
{
    public:
        virtual ~Data() = default;

        virtual void serialize() = 0;
        virtual void unserialize() = 0;

        const std::string dataType;
        char* message;

    protected:
        Data(std::string _dataType);
};


};

#endif // !DATA_H_