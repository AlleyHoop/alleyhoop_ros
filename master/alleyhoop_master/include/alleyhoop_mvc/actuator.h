#ifndef ACTUATOR_H_
#define ACTUATOR_H_

#include <string>

namespace AlleyHoopMVC
{
    class Actuator
    {
        public:
            virtual ~Actuator() = default;
            virtual void update() = 0;

            const std::string name;

	    protected:
	        Actuator(std::string n) : name(n)  {};
    };
}

#endif //! ACTUATOR_H_