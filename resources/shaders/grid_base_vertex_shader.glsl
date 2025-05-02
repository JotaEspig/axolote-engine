#version 330 core
layout(location = 0) in vec3 axolote_layout_pos;
layout(location = 1) in vec4 axolote_layout_color;

out vec4 axolote_in_color;
out vec3 axolote_in_vertex_position;

uniform mat4 axolote_gmesh_model;
uniform mat4 axolote_scene_camera;

void main() {
    vec4 current_pos = axolote_gmesh_model * vec4(axolote_layout_pos, 1.0);
    axolote_in_vertex_position = axolote_layout_pos;
    axolote_in_color = axolote_layout_color;
    gl_Position = axolote_scene_camera * current_pos;
}
