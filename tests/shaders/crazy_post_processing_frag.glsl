#version 330 core

// Output color
out vec4 FragColor;

in vec2 axolote_tex_coord;

// Texture info
uniform sampler2D axolote_diffuse0;

void main() {
    // Reverse texture colors
    FragColor = vec4(vec3(1.0 - texture(axolote_diffuse0, axolote_tex_coord)), 1.0);
}
