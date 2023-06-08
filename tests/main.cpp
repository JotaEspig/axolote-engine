#include <iostream>

#include <axolote/window.hpp>

int main(int argc, char **argv)
{
    std::cout << "hello world axolote engine!" << std::endl;
    auto w = axolote::Window(argc, argv);
    w.main_loop();
    return 0;
}
