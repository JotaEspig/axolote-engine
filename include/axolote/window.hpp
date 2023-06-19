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
        uint16_t _width;
        uint16_t _height;
        Color _color;
        GLFWwindow *window;

        void init();
        void process_input();

    public:
        Window();
        ~Window();
        std::string title();
        void set_title(std::string new_title);
        uint16_t width();
        void set_width(uint16_t new_width);
        uint16_t height();
        void set_height(uint16_t new_height);
        Color color();
        void set_color(uint8_t r, uint8_t g, uint8_t b, float opacity = 1.0f);
        void main_loop();
    };
}
