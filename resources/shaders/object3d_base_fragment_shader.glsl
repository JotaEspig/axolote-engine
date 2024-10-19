#version 330 core

// Different types of light casters
struct axolote_PointLight {
    vec3 color;
    bool is_set;
    vec3 pos;
    float constant;
    float linear;
    float quadratic;
};

struct axolote_DirectionalLight {
    vec3 color;
    bool is_set;
    vec3 dir;
    float intensity;
};

struct axolote_SpotLight {
    vec3 color;
    bool is_set;
    vec3 pos;
    vec3 dir;
    float cut_off;
    float outer_cut_off;
    float constant;
    float linear;
    float quadratic;
};

// Output color
out vec4 FragColor;

// Input variables
in vec4 axolote_color;
in vec2 axolote_tex_coord;
in vec3 axolote_normal;
in vec3 axolote_current_pos;

// Object info
uniform bool axolote_is_affected_by_lights;
uniform bool axolote_is_affected_by_lights_set;

// Scene info
uniform vec3 axolote_camera_pos;
uniform vec3 axolote_ambient_light;
uniform float axolote_ambient_light_intensity;
uniform float axolote_gamma = 1.0f;

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
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec_amount
        = pow(max(dot(view_direction, halfway_direction), 0.0f), 16);
    float specular = spec_amount * specular_light;

    // Apply attenuation to the light
    float distance = length(light.pos - axolote_current_pos);
    float attenuation = 1.0f / (light.constant + light.linear * distance
                + light.quadratic * distance * distance);

    diffuse *= attenuation;
    specular *= attenuation;

    vec3 diffuse_light_color = light.color.rgb * (diffuse + axolote_ambient_light_intensity);

    float specular_map = axolote_get_specular_map();
    float specular_light_color = specular_map * specular;

    return (diffuse_light_color + specular_light_color) * light.color.rgb;
}

vec3 axolote_calculate_directional_light(axolote_DirectionalLight light) {
    vec3 normal = normalize(axolote_normal);
    vec3 light_direction = normalize(-light.dir);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    float specular_light = 0.25f;
    vec3 view_direction = normalize(axolote_camera_pos - axolote_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec_amount
        = pow(max(dot(view_direction, halfway_direction), 0.0f), 16);
    float specular = spec_amount * specular_light;

    vec3 diffuse_light_color = light.color.rgb * (diffuse + axolote_ambient_light_intensity);

    float specular_map = axolote_get_specular_map();
    float specular_light_color = specular_map * specular;

    return (diffuse_light_color + specular_light_color) * light.color.rgb * light.intensity;
}

vec3 axolote_calculate_spot_light(axolote_SpotLight light) {
    vec3 normal = normalize(axolote_normal);
    vec3 light_direction = normalize(light.pos - axolote_current_pos);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    float specular_light = 0.25f;
    vec3 view_direction = normalize(axolote_camera_pos - axolote_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec_amount
        = pow(max(dot(view_direction, halfway_direction), 0.0f), 16);
    float specular = spec_amount * specular_light;

    // Apply attenuation to the light
    float distance = length(light.pos - axolote_current_pos);
    float attenuation = 1.0f / (light.constant + light.linear * distance
                + light.quadratic * distance * distance);

    diffuse *= attenuation;
    specular *= attenuation;

    // Apply smooth edges to the spot light
    float theta = dot(light_direction, normalize(-light.dir));
    float epsilon = light.cut_off - light.outer_cut_off;
    float intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0f, 1.0f);

    diffuse *= intensity;
    specular *= intensity;

    vec3 diffuse_light_color = light.color.rgb * diffuse;

    float specular_map = axolote_get_specular_map();
    float specular_light_color = specular_map * specular;

    return (diffuse_light_color + specular_light_color) * light.color.rgb;
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

    color.r = max(color.r, axolote_ambient_light.r * axolote_ambient_light_intensity);
    color.g = max(color.g, axolote_ambient_light.g * axolote_ambient_light_intensity);
    color.b = max(color.b, axolote_ambient_light.b * axolote_ambient_light_intensity);
    return color;
}

void main() {
    vec4 temp_frag_color = axolote_color;
    if (axolote_is_tex_set) {
        temp_frag_color = texture(axolote_diffuse0, axolote_tex_coord);
        if (temp_frag_color.a < 0.1f) {
            discard;
        }
    }

    bool should_use_light = axolote_num_point_lights
            + axolote_num_directional_lights
            + axolote_num_spot_lights > 0;

    // Prevents previous uniform from being used
    if (axolote_is_affected_by_lights_set)
        should_use_light = should_use_light && axolote_is_affected_by_lights;

    if (should_use_light) {
        vec3 light_influence_color = axolote_calculate_light();
        FragColor = temp_frag_color * vec4(light_influence_color, 1.0f);
    }
    else {
        FragColor = temp_frag_color;
    }

    FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / axolote_gamma));
}
