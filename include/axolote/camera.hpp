#pragma once

namespace axolote
{
    class Camera
    {
    public:
        float speed = 0.5f;
        struct
        {
            float x;
            float y;
            float z;
        } pos;
        struct
        {
            float x;
            float y;
            float z;
        } front;
        struct
        {
            float x;
            float y;
            float z;
        } up;
        
        Camera();

        void forward();
        void left();
        void right();
        void backwards();
    };
}
