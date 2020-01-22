#ifndef SENSOR_H_
#define SENSOR_H_

#include <string>



namespace AlleyHoopMVC
{
    //* An abstract sensor class
    /**
    * A class for indentifying sensors based on names
    *
    */
    class Sensor
    {
        public:
            /*!
            * \brief The default destructor for the sensor class
            * Is virtual, so will call the child class destructor aswell
            */
            virtual ~Sensor() = default;

            /*!
            * \brief The pure virtual update function.
            * Is generally called from the child controller class
            */
            virtual void update() = 0; 

            const std::string name; /**< the name of the sensor */
            

	    protected:
            /*!
            * \brief The default constructor for the sensor class
            * \param _name parameter for setting the name of the sensor
            */
	        Sensor(std::string _name) : name(_name)  {};
    };
}

#endif //! SENSOR_H_