#include "controller.hpp"
#include <memory>
int main()
{
    std::shared_ptr<hurrydocgo::Controller> p_controller(new hurrydocgo::Controller);
    p_controller->Init();
    return 0;
}