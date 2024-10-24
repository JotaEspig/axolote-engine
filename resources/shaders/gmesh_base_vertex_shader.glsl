#version 330 core
layout(location = 0) in vec3 axolote_aPos;
layout(location = 1) in vec4 axolote_aColor;
layout(location = 2) in vec2 axolote_aTex;
layout(location = 3) in vec3 axolote_aNormal;

out vec4 axolote_color;
out vec2 axolote_tex_coord;
out vec3 axolote_current_pos;

uniform mat4 axolote_model;

// WARNING: This uniform is NOT set in the
// GMesh class, you have to set them manually
uniform mat4 axolote_camera;

void main() {
    axolote_current_pos = vec3(axolote_model * vec4(axolote_aPos, 1.0f));
    axolote_tex_coord = axolote_aTex;
    axolote_color = axolote_aColor;

    gl_Position = axolote_camera * vec4(axolote_current_pos, 1.0f);
}
