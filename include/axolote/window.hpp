#pragma once

namespace axolote
{
    class Window
    {
    public:
        Window(int argc, char **argv);
        ~Window();
        void init(int argc, char **argv);
        void main_loop();

    private:
    };
}
