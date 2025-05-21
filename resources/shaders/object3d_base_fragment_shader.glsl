#version 420 core

struct axolote_PointLight {
    vec3 color;
    bool is_set; // 4-byte int
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
in vec4 axolote_in_color;
in vec2 axolote_in_tex_coord;
in vec3 axolote_in_normal;
in vec3 axolote_in_current_pos;

// Object info
uniform bool axolote_object3d_is_affected_by_lights;
uniform bool axolote_object3d_is_affected_by_lights_set;

// Scene info
uniform vec3 axolote_camera_pos;
uniform vec3 axolote_scene_ambient_light;
uniform float axolote_scene_ambient_light_intensity;
uniform float axolote_scene_gamma = 1.0f;

// Texture info
uniform sampler2D axolote_gmesh_diffuse0;
uniform sampler2D axolote_gmesh_specular0;
uniform bool axolote_gmesh_is_tex_set;
uniform bool axolote_gmesh_is_spec_map_set;

// Scene lights
const int axolote_NUM_MAX_LIGHTS = 50;

// TODO use binding point
layout(std140, binding = 0) uniform AxoloteLightsUBO {
    axolote_PointLight axolote_scene_point_lights[axolote_NUM_MAX_LIGHTS];
    // std140 memory layout rules apply here.
    // For axolote_PointLight (vec3, bool, vec3, float, float, float):
    //   vec3 color;       // offset 0 (aligned to 16 bytes)
    //   bool is_set;      // offset 12 (assuming bool is 4 bytes, aligned to 4)
    //   vec3 pos;         // offset 16 (aligned to 16 bytes)
    //   float constant;   // offset 28 (aligned to 4 bytes)
    //   float linear;     // offset 32 (aligned to 4 bytes)
    //   float quadratic;  // offset 36 (aligned to 4 bytes)
    // Total size: 40 bytes. Padded to 48 bytes (multiple of largest member alignment, 16).

    axolote_DirectionalLight axolote_scene_dir_lights[axolote_NUM_MAX_LIGHTS];
    // For axolote_DirectionalLight (vec3, bool, vec3, float):
    //   vec3 color;       // offset 0 (aligned to 16)
    //   bool is_set;      // offset 12 (aligned to 4)
    //   vec3 dir;         // offset 16 (aligned to 16)
    //   float intensity;  // offset 28 (aligned to 4)
    // Total size: 32 bytes (multiple of 16).

    axolote_SpotLight axolote_scene_spot_lights[axolote_NUM_MAX_LIGHTS];
    // For axolote_SpotLight (vec3, bool, vec3, vec3, float, float, float, float, float):
    //   vec3 color;           // offset 0 (aligned to 16)
    //   bool is_set;          // offset 12 (aligned to 4)
    //   vec3 pos;             // offset 16 (aligned to 16)
    //   vec3 dir;             // offset 32 (aligned to 16, next multiple of 16 after pos end)
    //   float cut_off;       // offset 44 (aligned to 4)
    //   float outer_cut_off; // offset 48 (aligned to 4)
    //   float constant;       // offset 52 (aligned to 4)
    //   float linear;         // offset 56 (aligned to 4)
    //   float quadratic;      // offset 60 (aligned to 4)
    // Total size: 64 bytes (multiple of 16).

    // Light counts
    int axolote_scene_num_point_lights;
    int axolote_scene_num_dir_lights;
    int axolote_scene_num_spot_lights;
};

float axolote_get_specular_map() {
    if (axolote_gmesh_is_spec_map_set)
        return texture(axolote_gmesh_specular0, axolote_in_tex_coord).r;
    else
        return axolote_in_color.r; // Or a default material specular value
}

vec3 axolote_calculate_point_light(axolote_PointLight light) {
    vec3 normal = normalize(axolote_in_normal);
    vec3 light_direction = normalize(light.pos - axolote_in_current_pos);
    float diffuse = max(dot(normal, light_direction), 0.0f);

    float specular_strength_factor = 0.25f; // Consider making this a material property
    vec3 view_direction = normalize(axolote_camera_pos - axolote_in_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec_amount = pow(max(dot(halfway_direction, normal), 0.0f), 16);

    float specular = spec_amount * specular_strength_factor;

    float distance = length(light.pos - axolote_in_current_pos);
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * distance * distance);

    diffuse *= attenuation;
    specular *= attenuation;

    vec3 diffuse_calc = light.color.rgb * diffuse;
    vec3 specular_calc = light.color.rgb * axolote_get_specular_map() * specular; // Modulate specular by light color too

    return diffuse_calc + specular_calc;
}

vec3 axolote_calculate_point_light_corrected(axolote_PointLight light) {
    vec3 normal = normalize(axolote_in_normal);
    vec3 light_dir_frag = light.pos - axolote_in_current_pos;
    float distance = length(light_dir_frag);
    vec3 light_direction = light_dir_frag / distance;

    // Diffuse
    float diff = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse_contrib = diff * light.color;

    // Specular (Blinn-Phong)
    float material_shininess = 16.0f; // Could be a uniform/material property
    float specular_strength = 0.25f; // Could be part of light or material
    vec3 view_direction = normalize(axolote_camera_pos - axolote_in_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec = pow(max(dot(normal, halfway_direction), 0.0f), material_shininess);
    vec3 specular_contrib = specular_strength * spec * light.color * axolote_get_specular_map();

    // Attenuation
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return attenuation * (diffuse_contrib + specular_contrib);
}

vec3 axolote_calculate_directional_light_corrected(axolote_DirectionalLight light) {
    vec3 normal = normalize(axolote_in_normal);
    vec3 light_direction = normalize(-light.dir);

    // Diffuse
    float diff = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse_contrib = diff * light.color;

    // Specular
    float material_shininess = 16.0f;
    float specular_strength = 0.25f;
    vec3 view_direction = normalize(axolote_camera_pos - axolote_in_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec = pow(max(dot(normal, halfway_direction), 0.0f), material_shininess);
    vec3 specular_contrib = specular_strength * spec * light.color * axolote_get_specular_map();

    return light.intensity * (diffuse_contrib + specular_contrib);
}

vec3 axolote_calculate_spot_light_corrected(axolote_SpotLight light) {
    vec3 normal = normalize(axolote_in_normal);
    vec3 light_dir_frag = light.pos - axolote_in_current_pos;
    float distance = length(light_dir_frag);
    vec3 light_direction = light_dir_frag / distance; // Normalized

    // Spotlight Intensity (cutoff)
    float theta = dot(light_direction, normalize(-light.dir));
    float epsilon = light.cut_off - light.outer_cut_off;
    float spot_intensity = clamp((theta - light.outer_cut_off) / epsilon, 0.0, 1.0);
    // If spot_intensity is 0, can early exit
    if (spot_intensity == 0.0) return vec3(0.0);

    // Diffuse
    float diff = max(dot(normal, light_direction), 0.0f);
    vec3 diffuse_contrib = diff * light.color;

    // Specular
    float material_shininess = 16.0f;
    float specular_strength = 0.25f;
    vec3 view_direction = normalize(axolote_camera_pos - axolote_in_current_pos);
    vec3 halfway_direction = normalize(light_direction + view_direction);
    float spec = pow(max(dot(normal, halfway_direction), 0.0f), material_shininess);
    vec3 specular_contrib = specular_strength * spec * light.color * axolote_get_specular_map();

    // Attenuation
    float attenuation = 1.0f / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

    return spot_intensity * attenuation * (diffuse_contrib + specular_contrib);
}

vec3 axolote_calculate_light() {
    vec3 total_light_color = vec3(0.0f);

    // Point lights
    for (int i = 0; i < axolote_scene_num_point_lights; ++i) {
        if (!axolote_scene_point_lights[i].is_set) continue;
        total_light_color += axolote_calculate_point_light_corrected(axolote_scene_point_lights[i]);
    }

    // Directional lights
    for (int i = 0; i < axolote_scene_num_dir_lights; ++i) {
        if (!axolote_scene_dir_lights[i].is_set) continue;
        total_light_color += axolote_calculate_directional_light_corrected(axolote_scene_dir_lights[i]);
    }

    // Spot lights
    for (int i = 0; i < axolote_scene_num_spot_lights; ++i) {
        if (!axolote_scene_spot_lights[i].is_set) continue;
        total_light_color += axolote_calculate_spot_light_corrected(axolote_scene_spot_lights[i]);
    }

    vec3 ambient_color = axolote_scene_ambient_light * axolote_scene_ambient_light_intensity;
    return total_light_color + ambient_color;
}

void main() {
    vec4 base_color = axolote_in_color;
    if (axolote_gmesh_is_tex_set) {
        base_color = texture(axolote_gmesh_diffuse0, axolote_in_tex_coord);
        if (base_color.a < 0.1f) { // Alpha test
            discard;
        }
    }

    bool should_use_light = (axolote_scene_num_point_lights +
            axolote_scene_num_dir_lights +
            axolote_scene_num_spot_lights) > 0;

    if (axolote_object3d_is_affected_by_lights_set) {
        should_use_light = should_use_light && axolote_object3d_is_affected_by_lights;
    }

    FragColor = base_color;
    if (should_use_light) {
        vec3 light_color = axolote_calculate_light();
        FragColor *= vec4(light_color, 1.0f);
    }

    // Gamma correction
    FragColor.rgb = pow(FragColor.rgb, vec3(1.0 / axolote_scene_gamma));
}
