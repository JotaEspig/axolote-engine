#include <iostream>

#include <axolote/engine.hpp>

int main(int argc, char **argv)
{
    std::cout << "hello world axolote engine!" << std::endl;
    auto w = axolote::Window();
    w.set_title("Axolote Engine Test");
    w.set_width(600);
    w.set_height(600);
    w.set_color(0x0f, 0x0f, 0x0f);
    w.main_loop();
    return 0;
}
