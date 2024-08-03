#version 330 core

// Output color
out vec4 FragColor;

// Input variables
in vec4 axolote_color;
in vec3 axolote_vertex_position;

uniform vec3 axolote_camera_pos;
uniform int axolote_grid_size;

void main() {
    // the closest to the center the brighter
    float distance = distance(axolote_camera_pos, axolote_vertex_position);
    float normalized_distance = distance / axolote_grid_size;
    float opacity = 1 - clamp(pow(normalized_distance, 1.5), 0, 1);
    FragColor = vec4(axolote_color.rgb, opacity);
}
