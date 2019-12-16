#include "alleyhoop_controller.h"

int main(int argc, char **argv)
{
    Controller controller = AlleyHoopController(argc, argv);
    
    while(true)
    {
        controller.update();
    }

    return 0;
}
