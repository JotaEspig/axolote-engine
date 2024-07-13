#version 330 core

// Different types of light casters
struct PointLight {
    vec3 color;
    bool is_set;
    vec3 pos;
};

struct DirectionalLight {
    vec3 color;
    bool is_set;
    vec3 dir;
};

struct SpotLight {
    vec3 color;
    bool is_set;
    vec3 pos;
    vec3 dir;
    float cut_off_angle;
};

// Output color
out vec4 FragColor;

// Input variables
in vec3 color;
in vec2 tex_coord;
in vec3 normal;
in vec3 current_pos;

// Scene info
uniform vec3 camera_pos;
uniform float ambient;

// Scene lights
const int NUM_MAX_LIGHTS = 50;
uniform int num_point_lights;
uniform int num_directional_lights;
uniform int num_spot_lights;

uniform PointLight point_lights[NUM_MAX_LIGHTS];
uniform DirectionalLight directional_lights[NUM_MAX_LIGHTS];
uniform SpotLight spot_lights[NUM_MAX_LIGHTS];

// Texture info
uniform sampler2D diffuse0;
uniform sampler2D specular0;
uniform bool is_tex_set;
uniform bool is_specular_map_set;

float get_specular_map() {
    if (is_specular_map_set)
        return texture(specular0, tex_coord).r;
    else
        return color.r;
}

vec3 calculate_point_light(PointLight light) {
    vec3 normal = normalize(normal);
    vec3 light_direction = normalize(light.pos - current_pos);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    float specular_light = 0.25f;
    vec3 view_direction = normalize(camera_pos - current_pos);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float spec_amount
        = pow(max(dot(view_direction, reflection_direction), 0.0f), 16);
    float specular = spec_amount * specular_light;

    vec3 diffuse_light_color = light.color.rgb * (diffuse + ambient);

    float specular_map = get_specular_map();
    float specular_light_color = specular_map * specular;

    return (diffuse_light_color + specular_light_color) * light.color.rgb;
}

vec3 calculate_directional_light(DirectionalLight light) {
    return vec3(0.0f);
}

vec3 calculate_spot_light(SpotLight light) {
    return vec3(0.0f);
}

vec3 calculate_light() {
    vec3 color = vec3(0.0f);

    // Point lights
    for (int i = 0; i < num_point_lights; ++i) {
        if (!point_lights[i].is_set) continue;
        color += calculate_point_light(point_lights[i]);
    }

    // Directional lights
    for (int i = 0; i < num_directional_lights; ++i) {
        if (!directional_lights[i].is_set) continue;
        color += calculate_directional_light(directional_lights[i]);
    }

    // Spot lights
    for (int i = 0; i < num_spot_lights; ++i) {
        if (!spot_lights[i].is_set) continue;
        color += calculate_spot_light(spot_lights[i]);
    }

    return color;
}

void main() {
    vec4 temp_frag_color = vec4(color, 1.0f);
    if (is_tex_set) {
        temp_frag_color = texture(diffuse0, tex_coord);
    }

    vec3 light_influence_color = calculate_light();
    FragColor = temp_frag_color * vec4(light_influence_color, 1.0f);
}
