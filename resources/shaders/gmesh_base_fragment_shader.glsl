#version 330 core

// Output color
out vec4 FragColor;

// Input variables
in vec4 axolote_in_color;
in vec2 axolote_in_tex_coord;
in vec3 axolote_in_current_pos;

// Texture info
uniform sampler2D axolote_gmesh_diffuse0;
uniform sampler2D axolote_gmesh_specular0;
uniform bool axolote_gmesh_is_tex_set;
uniform bool axolote_gmesh_is_spec_map_set;

float axolote_get_specular_map() {
    if (axolote_gmesh_is_spec_map_set)
        return texture(axolote_gmesh_specular0, axolote_in_tex_coord).r;
    else
        return axolote_in_color.r;
}

void main() {
    vec4 temp_frag_color = axolote_in_color;
    if (axolote_gmesh_is_tex_set) {
        temp_frag_color = texture(axolote_gmesh_diffuse0, axolote_in_tex_coord);
        if (temp_frag_color.a < 0.1f) {
            discard;
        }
    }

    FragColor = temp_frag_color;
}
