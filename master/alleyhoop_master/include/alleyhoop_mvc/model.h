#ifndef MODEL_H_
#define MODEL_H_

namespace AutonomousDriving
{

    class Model
    {
        public:
            virtual ~Model() = default;
            virtual bool update() = 0;
	    protected:
	        Model() {};
    };
}

#endif //! MODEL_H_
