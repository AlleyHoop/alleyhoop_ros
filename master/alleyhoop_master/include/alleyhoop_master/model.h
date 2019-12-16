#ifndef MODEL_H_
#define MODEL_H_

namespace AutonomousDriving
{

    class Model
    {
        public:
            virtual ~Model() = default;
            virtual void update() = 0;
	    protected:
	        Model() {};
    };
}

#endif //! MODEL_H_
