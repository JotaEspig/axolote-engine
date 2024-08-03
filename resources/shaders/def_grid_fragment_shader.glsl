#version 330 core

// Output color
out vec4 FragColor;

// Input variables
in vec4 axolote_color;
in float distance;

void main() {
    // the closest to the center the brighter
    float brightness = 10 / distance;
    FragColor = vec4(axolote_color.rgb, brightness * axolote_color.a);
}
