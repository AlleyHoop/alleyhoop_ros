#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <string>

namespace AlleyHoopMVC
{
    class Actuator
    {
        public:
            virtual ~Actuator() = default;

            const std::string name;

	    protected:
	        Actuator(std::string n) : name(n)  {};
    };
}

#endif //! ACTUATOR_H_