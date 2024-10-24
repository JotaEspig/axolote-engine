#version 330 core
layout(location = 0) in vec3 axolote_aPos;
layout(location = 1) in vec4 axolote_aColor;

out vec4 axolote_color;
out vec3 axolote_vertex_position;

uniform mat4 axolote_model;
uniform mat4 axolote_camera;

void main() {
    vec4 current_pos = axolote_model * vec4(axolote_aPos, 1.0);
    axolote_vertex_position = axolote_aPos;
    axolote_color = axolote_aColor;
    gl_Position = axolote_camera * current_pos;
}
