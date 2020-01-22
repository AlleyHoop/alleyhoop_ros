#ifndef VEHICLE_H_
#define VEHICLE_H_



#include <map>
#include "alleyhoop_mvc/actuator.h"

namespace AlleyHoopMVC
{
    //* An abstract vehicle class
    /**
    * The vehicle class in it self must be inherited and can then only be instantiated, the base class does :
    * 1. manages lifecyle of actuators
    * 2. to manage the lifecyle of actuators they must be added via the inheriting child class
    *
    */
   
    class Vehicle
    {
        public:
            /*!
            * \brief The main method to update the controller via the base class 
            */
            virtual bool update() = 0;

            /*!
            * \brief The destructor will delete all actuators 
            */
            virtual ~Vehicle()
            {
                for (std::map<std::string, Actuator*>::iterator it = actuators.begin(); it != actuators.end(); it++)
                {
                    std::cout << "deleted actuator " + it->second->name << std::endl;
                    delete it->second;
                }
            }

            /*!
            * \brief The main method to update all actuators and should be called from the child class
            */
            void updateActuators()
            {
                for (std::map<std::string, Actuator*>::iterator it = actuators.begin(); it != actuators.end(); it++)
                {
                    it->second->update();
                }
            }

            /*!
            * \brief The method to add actuators that need lifecyle management. Will return true if succesfully added an actuator
            * \param actuator parameter with a pointer to an actuator
            */
            bool addActuator(Actuator* actuator) 
            {
                if(actuators.find(actuator->name) == actuators.end())
                {
                    std::cout << "added actuator " + actuator->name << std::endl;
                    actuators.insert({actuator->name, actuator});
                    return true;
                }
                return false;
            };

            /*!
            * \brief Remove an acutator from the controller. Will return true if succesfully removed an actuator
            * \param name parameter with the name of an actuator
            */
            bool removeActuator(std::string name)
            {
                if(actuators.find(name) != actuators.end())
                {
                    std::cout << "removed and deleted actuator " + name << std::endl;
                    Actuator* s = actuators.find(name)->second;
                    actuators.erase(name);
                    delete s;
                    return true;
                }
                return false;
            };

            /*!
            * \brief Get a specific actuator from the controller. Returns a pointer to an acutator unless not existing, then will return a nullptr.
            * \param name parameter with the name of an acutator
            */
            Actuator* getActuator(std::string name)
            {
                if(actuators.find(name) == actuators.end())
                {
                    return nullptr;
                }
                return actuators.find(name)->second;
            };

	    protected:
            /*!
            * \brief The constructor of the vehicle
            */
	        Vehicle() {};

            std::map<std::string, Actuator*> actuators;  /**< A map for managing actuators based on their names */
    };

}

#endif //! VEHICLE_H_
