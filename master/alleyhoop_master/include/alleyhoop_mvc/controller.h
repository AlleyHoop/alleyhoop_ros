#ifndef CONTROLLER_H_
#define CONTROLLER_H_

//* An abstract controller class
/**
* The controller class in it self must be inherited and can then only be instantiated, the base class does :
* 1. manages lifecyle of sensors
* 2. to manage the lifecyle of sensors they must be added via the inheriting child class
*
*/

#include <map>
#include "alleyhoop_mvc/vehicle.h"
#include "alleyhoop_mvc/sensor.h"
#include <iostream>

namespace AlleyHoopMVC
{
    class Controller
    {
        public:
            /*!
            * \brief The main method to update the controller via the base class 
            */
            virtual bool update() = 0;

            /*!
            * \brief The destructor will delete all sensors 
            */
            virtual ~Controller()
            {
                for (std::map<std::string, Sensor*>::iterator it = sensors.begin(); it != sensors.end(); it++)
                {
                    std::cout << "deleted sensor " + it->second->name << std::endl;
                    delete it->second;
                }
            } 

            /*!
            * \brief The main method to update all sensors and should be called from the child class
            */
            void updateSensors()
            {
                for (std::map<std::string, Sensor*>::iterator it = sensors.begin(); it != sensors.end(); it++)
                {
                    it->second->update();
                }
            }

            /*!
            * \brief The method to add sensors that need lifecyle management. Will return true if succesfully added a sensor
            * \param sensor parameter with a pointer to a sensor
            */
            bool addSensor(Sensor* sensor) 
            {
                if(sensors.find(sensor->name) == sensors.end())
                {
                    std::cout << "added sensor " + sensor->name << std::endl;
                    sensors.insert({sensor->name, sensor});
                    return true;
                }
                return false;
            };

            /*!
            * \brief Remove a sensor from the controller. Will return true if succesfully removed a sensor
            * \param name parameter with the name of a sensor
            */
            bool removeSensor(std::string name)
            {
                if(sensors.find(name) != sensors.end())
                {
                    std::cout << "removed and deleted sensor " + name << std::endl;
                    Sensor* s = sensors.find(name)->second;
                    sensors.erase(name);
                    delete s;
                    return true;
                }
                return false;
            };

            /*!
            * \brief Get a specific sensor from the controller. Returns a pointer to a sensor unless not existing, then will return a nullptr.
            * \param name parameter with the name of a sensor
            */
            Sensor* getSensor(std::string name)
            {
                if(sensors.find(name) == sensors.end())
                {
                    return nullptr;
                }
                return sensors.find(name)->second;
            };

	    protected:
             /*!
            * \brief The constructor of the controller, it requires a vehicle to control
            * \param _vehicle a pointer to the vehicle to be controlled
            */
	        Controller(Vehicle* _vehicle) : vehicle(_vehicle)  {};
            
            Vehicle* vehicle; /**< A pointer to a vehicle to be controlled */
            std::map<std::string, Sensor*> sensors; /**< A map for managing sensors based on their names */
    };
}

#endif //! CONTROLLER_H_
