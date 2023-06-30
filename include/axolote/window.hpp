#pragma once

#define GLFW_INCLUDE_NONE

#include <string>
#include <cstdint>

#include <GLFW/glfw3.h>

#include <axolote/structs.hpp>

namespace axolote
{
    class Window
    {
    private:
        std::string _title;
        Color _color;
        GLFWwindow *window;

        void init();
        void process_input();

    public:
        Window();
        ~Window();
        std::string title();
        void set_title(std::string new_title);
        int width();
        void set_width(int new_width);
        int height();
        void set_height(int new_height);
        Color color();
        void set_color(uint8_t r, uint8_t g, uint8_t b, float opacity = 1.0f);
        void main_loop();
    };
}
