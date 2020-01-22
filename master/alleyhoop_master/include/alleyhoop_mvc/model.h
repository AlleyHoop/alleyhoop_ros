#ifndef MODEL_H_
#define MODEL_H_


namespace AlleyHoopMVC
{
    //* An abstract model class
    /**
    * The model class in self must be inherited and can then only be instantiated
    *
    */

    class Model
    {
        public:
            /*!
            * \brief The default destructor for the model class
            * Is virtual, so will call the child class destructor aswell
            */
            virtual ~Model() = default;

	    protected:
            /*!
            * \brief The default constructor for the model class
            */
	        Model() {};
    };
}

#endif //! MODEL_H_
