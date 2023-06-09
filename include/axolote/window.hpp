#pragma once

#include <string>
#include <cstdint>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace axolote
{
    class Window
    {
    private:
        GLFWwindow *window;

        void init();
        void process_input();

    public:
        std::string title;
        uint16_t width;
        uint16_t height;

        Window();
        ~Window();
        void main_loop();
    };
}
