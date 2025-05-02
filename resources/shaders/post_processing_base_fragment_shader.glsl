#version 330 core

// Output color
out vec4 FragColor;

in vec2 axolote_in_tex_coord;

// Texture info
uniform sampler2D axolote_gmesh_diffuse0;

void main() {
    FragColor = texture(axolote_gmesh_diffuse0, axolote_in_tex_coord);
}
