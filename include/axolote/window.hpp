/**
 * \file window.hpp
 * \brief GLFWwindow operations handler
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 **/
#pragma once

#define GLFW_INCLUDE_NONE

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>

#include "axolote/scene.hpp"
#include "axolote/structs.hpp"

namespace axolote {

/**
 * \brief Window handler
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version May 23, 2024
 *
 * This class take care of GLFW window object and input process
 **/
class Window {
public:
    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    Window();
    /**
     * \brief Constructor with Vsync
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     * \param vsync - should use vsync
     **/
    Window(bool vsync);
    /**
     * \brief Destructor
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    ~Window();

    /**
     * \brief initializes window
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    void init();
    /**
     * \brief process user input
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     *
     * Preconfigured way to process SPACE, SHIFT, CTRL and mouse movement
     * (this method can be overrided)
     **/
    void process_input(float delta_t = 1.0f);
    /**
     * \brief process the simplest user input (AWSD)
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param delta_t - time difference from last frame
     *
     * Preconfigured way to process A, W, S and D keys
     * (this method can be overrided)
     **/
    void minimal_process_input(float delta_t = 1.0f);
    /**
     * \brief checks if window should close
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    bool should_close();
    /**
     * \brief Flush the buffers. Should be called at the end of the main loop
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     **/
    void flush();

    /**
     * \brief Get the state of vsync
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     * \return return vsync member
     **/
    bool vsync() const;
    /**
     * \brief Enable or disable vsync
     * \author João Vitor Espig (JotaEspig)
     * \date May 24, 2024
     * \version May 24, 2024
     * \param vsync - should use vsync
     **/
    void set_vsync(bool vsync);
    /**
     * \brief title getter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    std::string title() const;
    /**
     * \brief title setter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param new_title - new window title
     **/
    void set_title(std::string new_title);
    /**
     * \brief width getter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    int width() const;
    /**
     * \brief width setter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param new_width - new window width
     **/
    void set_width(int new_width);
    /**
     * \brief height getter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    int height() const;
    /**
     * \brief height setter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param new_height - new window height
     **/
    void set_height(int new_height);
    /**
     * \brief color getter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     **/
    Color color() const;
    /**
     * \brief color setter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param color - Color object
     **/
    void set_color(const Color &color);
    /**
     * \brief color setter
     * \author João Vitor Espig (JotaEspig)
     * \date October 04, 2023
     * \version October 04, 2023
     * \param r - Red in RGB
     * \param g - Green in RGB
     * \param b - Blue in RGB
     * \param opacity - alpha param
     **/
    void set_color(uint8_t r, uint8_t g, uint8_t b, float opacity = 1.0f);

protected:
    /** should use vsync **/
    bool _vsync = true;
    /** window title **/
    std::string _title;
    /** window background color **/
    Color _color;
    /** GLFWwindow struct object **/
    GLFWwindow *window;
    /** Current scene **/
    std::shared_ptr<Scene> current_scene;
    /** map to pressed keys **/
    std::unordered_map<int, bool> _keys_pressed;
};

} // namespace axolote
