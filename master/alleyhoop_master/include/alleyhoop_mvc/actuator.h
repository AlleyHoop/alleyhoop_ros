#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <string>

namespace AutonomousDriving
{
    class Actuator
    {
        public:
            virtual ~Actuator() = default;
            virtual bool update() = 0;

            const std::string name;

	    protected:
	        Actuator(std::string n) : name(n)  {};
    };
}

#endif //! ACTUATOR_H_