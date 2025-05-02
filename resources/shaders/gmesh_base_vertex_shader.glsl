#version 330 core
layout(location = 0) in vec3 axolote_layout_pos;
layout(location = 1) in vec4 axolote_layout_color;
layout(location = 2) in vec2 axolote_layout_tex_coord;
layout(location = 3) in vec3 axolote_layout_normal;

out vec4 axolote_in_color;
out vec2 axolote_in_tex_coord;
out vec3 axolote_in_current_pos;

uniform mat4 axolote_gmesh_model;

uniform mat4 axolote_scene_camera;

void main() {
    axolote_in_current_pos = vec3(axolote_gmesh_model * vec4(axolote_layout_pos, 1.0f));
    axolote_in_tex_coord = axolote_layout_tex_coord;
    axolote_in_color = axolote_layout_color;

    gl_Position = axolote_scene_camera * vec4(axolote_in_current_pos, 1.0f);
}
