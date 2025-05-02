#version 330 core
layout(location = 0) in vec3 axolote_layout_pos;
layout(location = 2) in vec2 axolote_layout_tex_coord;

out vec2 axolote_in_tex_coord;

void main()
{
    gl_Position = vec4(axolote_layout_pos.x, axolote_layout_pos.y, 0.0, 1.0);
    axolote_in_tex_coord = axolote_layout_tex_coord;
}
