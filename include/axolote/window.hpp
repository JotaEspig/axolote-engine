/**
 * @file window.hpp
 * @brief GLFWwindow operations handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#define GLFW_INCLUDE_NONE

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>

#include <GLFW/glfw3.h>
#include <imgui.h>

#include "axolote/scene.hpp"
#include "axolote/structs.hpp"

namespace axolote {

/**
 * @brief Window handler
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This class take care of GLFW window object and input process
 **/
class Window {
public:
    enum class MouseKey {
        LEFT = GLFW_MOUSE_BUTTON_LEFT,
        RIGHT = GLFW_MOUSE_BUTTON_RIGHT,
        MIDDLE = GLFW_MOUSE_BUTTON_MIDDLE,
        FOUR = GLFW_MOUSE_BUTTON_4,
        FIVE = GLFW_MOUSE_BUTTON_5,
        SIX = GLFW_MOUSE_BUTTON_6,
        SEVEN = GLFW_MOUSE_BUTTON_7,
        EIGHT = GLFW_MOUSE_BUTTON_8
    };
    enum class MouseKeyState { PRESSED = GLFW_PRESS, RELEASED = GLFW_RELEASE };
    enum class CursorMode {
        NORMAL = GLFW_CURSOR_NORMAL,
        HIDDEN = GLFW_CURSOR_HIDDEN,
        DISABLED = GLFW_CURSOR_DISABLED
    };
    enum class Key {
        SPACE = GLFW_KEY_SPACE,
        APOSTROPHE = GLFW_KEY_APOSTROPHE, /*,*/
        COMMA = GLFW_KEY_COMMA,           /* ,*/
        MINUS = GLFW_KEY_MINUS,           /* - */
        PERIOD = GLFW_KEY_PERIOD,         /* .*/
        SLASH = GLFW_KEY_SLASH,           /* / */
        ZERO = GLFW_KEY_0,
        ONE = GLFW_KEY_1,
        TWO = GLFW_KEY_2,
        THREE = GLFW_KEY_3,
        FOUR = GLFW_KEY_4,
        FIVE = GLFW_KEY_5,
        SIX = GLFW_KEY_6,
        SEVEN = GLFW_KEY_7,
        EIGHT = GLFW_KEY_8,
        NINE = GLFW_KEY_9,
        EQUAL = GLFW_KEY_EQUAL, /* = */
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,   /* [ */
        BACKSLASH = GLFW_KEY_BACKSLASH,         /* \ */
        RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET, /* ] , */
        GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,   /* ` */
        WORLD_1 = GLFW_KEY_WORLD_1,             /* non-US #1 */
        WORLD_2 = GLFW_KEY_WORLD_2,             /* non-US #2 */
        ESCAPE = GLFW_KEY_ESCAPE,
        ENTER = GLFW_KEY_ENTER,
        TAB = GLFW_KEY_TAB,
        BACKSPACE = GLFW_KEY_BACKSPACE,
        INSERT = GLFW_KEY_INSERT,
        DELETE = GLFW_KEY_DELETE,
        RIGHT = GLFW_KEY_RIGHT,
        LEFT = GLFW_KEY_LEFT,
        DOWN = GLFW_KEY_DOWN,
        UP = GLFW_KEY_UP,
        PAGE_UP = GLFW_KEY_PAGE_UP,
        PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
        HOME = GLFW_KEY_HOME,
        END = GLFW_KEY_END,
        CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
        SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
        NUM_LOCK = GLFW_KEY_NUM_LOCK,
        PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
        PAUSE = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
        KP_0 = GLFW_KEY_KP_0,
        KP_1 = GLFW_KEY_KP_1,
        KP_2 = GLFW_KEY_KP_2,
        KP_3 = GLFW_KEY_KP_3,
        KP_4 = GLFW_KEY_KP_4,
        KP_5 = GLFW_KEY_KP_5,
        KP_6 = GLFW_KEY_KP_6,
        KP_7 = GLFW_KEY_KP_7,
        KP_8 = GLFW_KEY_KP_8,
        KP_9 = GLFW_KEY_KP_9,
        KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
        KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
        KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
        KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
        KP_ADD = GLFW_KEY_KP_ADD,
        KP_ENTER = GLFW_KEY_KP_ENTER,
        KP_EQUAL = GLFW_KEY_KP_EQUAL,
        LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
        LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
        LEFT_ALT = GLFW_KEY_LEFT_ALT,
        LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
        RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
        RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
        RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
        RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
        MENU = GLFW_KEY_MENU,
        LAST = GLFW_KEY_LAST,
    };
    enum class KeyState {
        PRESSED = GLFW_PRESS,
        RELEASED = GLFW_RELEASE,
        REPEAT = GLFW_REPEAT
    };

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Window();
    /**
     * @brief Constructor with Vsync
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vsync should use vsync
     **/
    Window(bool vsync);
    /**
     * @brief Destructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    ~Window();

    /**
     * @brief Default framebuffer size callback
     *
     * @param window GLFWwindow pointer
     * @param width window width
     * @param height window height
     *
     * When you want to implement a custom framebuffer size callback, you can
     * use this method as a reference. And it's recommended to see the function
     * glfwGetWindowUserPointer.
     * you
     */
    static void default_framebuffer_size_callback(
        GLFWwindow *window, int width, int height
    );
    /**
     * @brief Default error callback
     *
     * @param error error code
     * @param description error description

     * When you want to implement a custom error callback, you can
     * use this method as a reference. And it's recommended to see the function
     * glfwGetWindowUserPointer.
     */
    static void default_error_callback(int error, const char *description);

    /**
     * @brief initializes window
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void init();
    /**
     * @brief poll events from GLFW
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void poll_events();
    /**
     * @brief get key state
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param key key to check
     * @returns KeyState enum
     **/
    KeyState get_key_state(Key key);

    MouseKeyState get_mouse_key_state(MouseKey key);
    /**
     * @brief returns if a key is pressed
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param key key to check
     * @returns true or false
     **/
    bool is_key_pressed(Key key) const;
    /**
     * @brief set a key as pressed or not
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param key key to set
     * @param value true or false
     **/
    void set_key_pressed(Key key, bool value);
    /**
     * @brief set the cursor mode
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param mode CursorMode enum
     **/
    void set_cursor_mode(CursorMode mode);
    /**
     * @brief get the cursor position
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param xpos x position
     * @param ypos y position
     **/
    void get_cursor_position(double *xpos, double *ypos);
    /**
     * @brief set the cursor position
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param xpos x position
     * @param ypos y position
     **/
    void set_cursor_position(double xpos, double ypos);
    /**
     * @brief process user input
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     *
     * Preconfigured way to process SPACE, SHIFT, CTRL and mouse movement
     * (this method can be overrided)
     **/
    void process_input(double delta_t = 1.0f);
    /**
     * @brief process the simplest user input (AWSD)
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param delta_t time difference from last frame
     *
     * Preconfigured way to process A, W, S and D keys
     * (this method can be overrided)
     **/
    void minimal_process_input(double delta_t = 1.0f);
    /**
     * @brief checks if window should close
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    bool should_close() const;
    /**
     * @brief set if window should close
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param value true or false
     **/
    void set_should_close(bool value);
    /**
     * @brief Clear the window with the background color
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void clear();
    /**
     * @brief Flush the buffers. Should be called at the end of the main loop
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void flush();
    /**
     * @param aspect_ratio camera aspect ratio
     **/
    void update_camera(float aspect_ratio);
    /**
     * @param delta_t time difference from last frame
     **/
    void update(double delta_t);
    /**
     * @brief Render the current scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void render();

    std::shared_ptr<Scene> current_scene() const;
    /**
     * @brief Set the current scene
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param scene Scene object pointer
     **/
    void set_scene(std::shared_ptr<Scene> scene);
    /**
     * @brief Get the state of vsync
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return return vsync member
     **/
    bool vsync() const;
    /**
     * @brief Enable or disable vsync
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param vsync should use vsync
     **/
    void set_vsync(bool vsync);
    /**
     * @brief Set the window to maximized
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void set_maximized();
    /**
     * @brief title getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    std::string title() const;
    /**
     * @brief title setter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param new_title new window title
     **/
    void set_title(std::string new_title);
    /**
     * @brief width getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    int width() const;
    /**
     * @brief height getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    int height() const;
    /**
     * @brief window size setter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param new_width new window width
     * @param new_height new window height
     **/
    void set_window_size(int new_width, int new_height);
    /**
     * @brief color getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Color color() const;
    /**
     * @brief color setter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param color Color object
     **/
    void set_color(const Color &color);
    /**
     * @brief color setter
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param r Red in RGB
     * @param g Green in RGB
     * @param b Blue in RGB
     * @param opacity alpha param
     **/
    void set_color(uint8_t r, uint8_t g, uint8_t b, float opacity = 1.0f);
    /**
     * @brief get the time since GLFW was initialized
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @returns time in seconds
     **/
    double get_time() const;
    /**
     * @brief Checks if the window should process mouse input. Can be overrided
     * by the user to implement custom behavior. by default it retuns
     * true
     *
     * @return true
     * @return false
     **/
    virtual bool should_process_mouse_input() const;
    /**
     * @brief Checks if the window should process keyboard input. Can be
     * overrided by the user to implement custom behavior. by default it retuns
     * true
     *
     * @return true
     * @return false
     **/
    virtual bool should_process_keyboard_input() const;
    /**
     * @brief get glfw window object pointer
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @returns GLFWwindow pointer
     *
     * Useful to set callbacks
     */
    GLFWwindow *window() const;

protected:
    /** window title **/
    std::string _title;
    /** window background color **/
    Color _color;
    /** ImGui IO object **/
    std::shared_ptr<ImGuiIO> _io;

private:
    /** GLFWwindow struct object **/
    GLFWwindow *_window;
    /** should use vsync **/
    bool _vsync = true;
    /** Current scene **/
    std::shared_ptr<Scene> _current_scene;
    /** map to pressed keys **/
    std::unordered_map<int, bool> _keys_pressed;
};

} // namespace axolote
