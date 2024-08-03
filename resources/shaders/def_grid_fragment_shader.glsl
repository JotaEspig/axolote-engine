#version 330 core

// Output color
out vec4 FragColor;

// Input variables
in vec4 axolote_color;
in vec3 axolote_vertex_position;

uniform int axolote_grid_size;
uniform float axolote_grid_fading_factor;

void main() {
    // the closest to the center the brighter
    float distance = length(axolote_vertex_position);
    float normalized_distance = distance / axolote_grid_size;
    float quadratic = axolote_grid_fading_factor * normalized_distance * normalized_distance;
    float opacity = 1 / (1 + quadratic);
    FragColor = vec4(axolote_color.rgb, opacity);
}
