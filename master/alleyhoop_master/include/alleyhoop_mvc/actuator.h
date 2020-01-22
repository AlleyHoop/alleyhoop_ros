#ifndef ACTUATOR_H_
#define ACTUATOR_H_

//* An abstract actuator class
/**
* A class for indentifying actuators based on names
*
*/

#include <string>

namespace AlleyHoopMVC
{
    class Actuator
    {
        public:
            /*!
            * \brief The default destructor for the actuator class
            * Is virtual, so will call the child class destructor aswell
            */
            virtual ~Actuator() = default;

            /*!
            * \brief The pure virtual update function.
            * Is generally called from the child controller class
            */
            virtual void update() = 0;

            const std::string name; /**< the name of the actuator */

	    protected:
            /*!
            * \brief The default constructor for the actuator class
            * \param _name parameter for setting the name of the actuator
            */
	        Actuator(std::string _name) : name(_name)  {};
            
    };
}

#endif //! ACTUATOR_H_