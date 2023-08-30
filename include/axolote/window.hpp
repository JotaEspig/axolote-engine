#pragma once

#define GLFW_INCLUDE_NONE

#include <string>
#include <cstdint>

#include <GLFW/glfw3.h>

#include <axolote/camera.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

class Window
{
private:
    std::string _title;
    Color _color;
    Camera camera;
    GLFWwindow *window;

    void init();

protected:
    void process_input();
    void minimal_process_input();
    bool should_close();

public:
    Window();
    ~Window();

    void main_loop();
    std::string title();
    void set_title(std::string new_title);
    int width();
    void set_width(int new_width);
    int height();
    void set_height(int new_height);
    Color color();
    void set_color(uint8_t r, uint8_t g, uint8_t b, float opacity = 1.0f);
};

} // namespace axolote
