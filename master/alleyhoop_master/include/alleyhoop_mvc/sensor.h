#ifndef SENSOR_H_
#define SENSOR_H_

#include <string>

namespace AlleyHoopMVC
{
    class Sensor
    {
        public:
            virtual ~Sensor() = default;

            const std::string name; 

	    protected:
	        Sensor(std::string n) : name(n)  {};
    };
}

#endif //! SENSOR_H_