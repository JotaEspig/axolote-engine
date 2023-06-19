#include <iostream>

#include <axolote/engine.hpp>

int main(int argc, char **argv)
{
    std::cout << "hello world axolote engine!" << std::endl;
    auto w = axolote::Window();
    w.set_title("Axolote Engine Test");
    w.set_width(800);
    w.set_height(800);
    w.set_color(0x00, 0x00, 0x00);
    w.main_loop();
    return 0;
}
