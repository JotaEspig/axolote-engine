#include <iostream>

#include <GL/glut.h>

#include <axolote/window.hpp>

int main()
{
    std::cout << "hello world axolote engine!" << std::endl;
    using namespace axolote;
    Window w = Window();
    std::cout << w.x << std::endl;
    return 0;
}
