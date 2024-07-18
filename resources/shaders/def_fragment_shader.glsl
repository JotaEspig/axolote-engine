#version 330 core

// Different types of light casters
struct axolote_PointLight {
    vec3 color;
    bool is_set;
    vec3 pos;
};

struct axolote_DirectionalLight {
    vec3 color;
    bool is_set;
    vec3 dir;
};

struct axolote_SpotLight {
    vec3 color;
    bool is_set;
    vec3 pos;
    vec3 dir;
    float cut_off_angle;
};

// Output color
out vec4 FragColor;

// Input variables
in vec3 axolote_color;
in vec2 axolote_tex_coord;
in vec3 axolote_normal;
in vec3 axolote_current_pos;

// Scene info
uniform vec3 axolote_camera_pos;
uniform float axolote_ambient;

// Scene lights
const int axolote_NUM_MAX_LIGHTS = 50;
uniform int axolote_num_point_lights;
uniform int axolote_num_directional_lights;
uniform int axolote_num_spot_lights;

uniform axolote_PointLight axolote_point_lights[axolote_NUM_MAX_LIGHTS];
uniform axolote_DirectionalLight axolote_directional_lights[axolote_NUM_MAX_LIGHTS];
uniform axolote_SpotLight axolote_spot_lights[axolote_NUM_MAX_LIGHTS];

// Texture info
uniform sampler2D axolote_diffuse0;
uniform sampler2D axolote_specular0;
uniform bool axolote_is_tex_set;
uniform bool axolote_is_specular_map_set;

float axolote_get_specular_map() {
    if (axolote_is_specular_map_set)
        return texture(axolote_specular0, axolote_tex_coord).r;
    else
        return axolote_color.r;
}

vec3 axolote_calculate_point_light(axolote_PointLight light) {
    vec3 normal = normalize(axolote_normal);
    vec3 light_direction = normalize(light.pos - axolote_current_pos);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    float specular_light = 0.25f;
    vec3 view_direction = normalize(axolote_camera_pos - axolote_current_pos);
    vec3 reflection_direction = reflect(-light_direction, normal);
    float spec_amount
        = pow(max(dot(view_direction, reflection_direction), 0.0f), 16);
    float specular = spec_amount * specular_light;

    vec3 diffuse_light_color = light.color.rgb * (diffuse + axolote_ambient);

    float specular_map = axolote_get_specular_map();
    float specular_light_color = specular_map * specular;

    return (diffuse_light_color + specular_light_color) * light.color.rgb;
}

vec3 axolote_calculate_directional_light(axolote_DirectionalLight light) {
    return vec3(0.0f);
}

vec3 axolote_calculate_spot_light(axolote_SpotLight light) {
    return vec3(0.0f);
}

vec3 axolote_calculate_light() {
    vec3 color = vec3(0.0f);

    // Point lights
    for (int i = 0; i < axolote_num_point_lights; ++i) {
        if (!axolote_point_lights[i].is_set) continue;
        color += axolote_calculate_point_light(axolote_point_lights[i]);
    }

    // Directional lights
    for (int i = 0; i < axolote_num_directional_lights; ++i) {
        if (!axolote_directional_lights[i].is_set) continue;
        color += axolote_calculate_directional_light(axolote_directional_lights[i]);
    }

    // Spot lights
    for (int i = 0; i < axolote_num_spot_lights; ++i) {
        if (!axolote_spot_lights[i].is_set) continue;
        color += axolote_calculate_spot_light(axolote_spot_lights[i]);
    }

    return color;
}

void main() {
    vec4 temp_frag_color = vec4(axolote_color, 1.0f);
    if (axolote_is_tex_set) {
        temp_frag_color = texture(axolote_diffuse0, axolote_tex_coord);
    }

    vec3 light_influence_color = axolote_calculate_light();
    FragColor = temp_frag_color * vec4(light_influence_color, 1.0f);
}
