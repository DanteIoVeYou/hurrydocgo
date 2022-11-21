#include "controller.hpp"
#include <memory>
int main()
{
    hurrydocgo::Controller *p_controller = new hurrydocgo::Controller;
    p_controller->Init();
    return 0;
}