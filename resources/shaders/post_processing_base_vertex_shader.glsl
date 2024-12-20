#version 330 core
layout(location = 0) in vec3 axolote_aPos;
layout(location = 2) in vec2 axolote_aTex;

out vec2 axolote_tex_coord;

void main()
{
    gl_Position = vec4(axolote_aPos.x, axolote_aPos.y, 0.0, 1.0);
    axolote_tex_coord = axolote_aTex;
}
