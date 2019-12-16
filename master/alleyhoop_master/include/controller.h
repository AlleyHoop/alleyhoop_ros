#ifndef CONTROLLER_H_
#define CONTROLLER_H_

namespace AutonomousDriving
{

    class Controller
    {
        public:
            virtual ~Controller() = default;
            virtual void update() = 0;
    }

}

#endif //! CONTROLLER_H_