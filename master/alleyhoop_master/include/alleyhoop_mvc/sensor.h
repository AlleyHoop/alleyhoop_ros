#ifndef SENSOR_H_
#define SENSOR_H_

#include <string>

namespace AutonomousDriving
{
    class Sensor
    {
        public:
            virtual ~Sensor() = default;
            virtual bool update() = 0;

            const std::string name; 

	    protected:
	        Sensor(std::string n) : name(n)  {};
    };
}

#endif //! SENSOR_H_