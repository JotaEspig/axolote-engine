#include <iostream>

#include <axolote/window.hpp>

int main(int argc, char **argv)
{
    std::cout << "hello world axolote engine!" << std::endl;
    auto w = new axolote::Window();
    w->title = "Testing";
    w->width = 1000;
    w->height = 800;
    w->main_loop();
    delete w;
    return 0;
}
