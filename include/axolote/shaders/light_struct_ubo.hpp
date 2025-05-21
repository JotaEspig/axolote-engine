/**
 * @file light_struct_ubo.hpp
 * @brief provides struct for lights UBO
 **/
#pragma once

#include <glm/glm.hpp>

#define SHADER_MAX_LIGHTS 50
#define SHADER_POINTLIGHT_STRUCT_SIZE 48
#define SHADER_DIRECTIONALLIGHT_STRUCT_SIZE 32
#define SHADER_SPOTLIGHT_STRUCT_SIZE 64
#define UBO_LIGHTS_DATA_SIZE                                   \
    (SHADER_MAX_LIGHTS * SHADER_POINTLIGHT_STRUCT_SIZE         \
     + SHADER_MAX_LIGHTS * SHADER_DIRECTIONALLIGHT_STRUCT_SIZE \
     + SHADER_MAX_LIGHTS * SHADER_SPOTLIGHT_STRUCT_SIZE)
#define UBO_LIGHT_COUNTS_SIZE (3 * 4) // 3 integers for counts
#define UBO_TOTAL_SIZE (UBO_LIGHTS_DATA_SIZE + UBO_LIGHT_COUNTS_SIZE)

namespace axolote {
namespace shaders {

// GLSL:
// struct axolote_PointLight {
//     vec3 color;
//     bool is_set; // Mapped to int
//     vec3 pos;
//     float constant;
//     float linear;
//     float quadratic;
// };
// std140 size: 48 bytes
struct PointLightStd140 {
    glm::vec3 color;   // offset 0 (12 bytes)
    int is_set;        // offset 12 (4 bytes, for GLSL bool)
    glm::vec3 pos;     // offset 16 (12 bytes)
    float constant;    // offset 28 (4 bytes)
    float linear;      // offset 32 (4 bytes)
    float quadratic;   // offset 36 (4 bytes)
    float _padding[2]; // offset 40 (8 bytes padding to fill 48 bytes struct
                       // size for array stride)
};
static_assert(
    sizeof(PointLightStd140) == SHADER_POINTLIGHT_STRUCT_SIZE,
    "PointLightStd140 size mismatch"
);

// GLSL:
// struct axolote_DirectionalLight {
//     vec3 color;
//     bool is_set; // Mapped to int
//     vec3 dir;
//     float intensity;
// };
// std140 size: 32 bytes
struct DirectionalLightStd140 {
    glm::vec3 color; // offset 0 (12 bytes)
    int is_set;      // offset 12 (4 bytes)
    glm::vec3 dir;   // offset 16 (12 bytes)
    float intensity; // offset 28 (4 bytes)
};
static_assert(
    sizeof(DirectionalLightStd140) == SHADER_DIRECTIONALLIGHT_STRUCT_SIZE,
    "DirectionalLightStd140 size mismatch"
);

// GLSL:
// struct axolote_SpotLight {
//     vec3 color;
//     bool is_set; // Mapped to int
//     vec3 pos;
//     vec3 dir;
//     float cut_off;
//     float outer_cut_off;
//     float constant;
//     float linear;
//     float quadratic;
// };
// std140 size: 64 bytes
struct SpotLightStd140 {
    glm::vec3 color;     // offset 0  (12 bytes)
    int is_set;          // offset 12 (4 bytes)
    glm::vec3 pos;       // offset 16 (12 bytes)
    float _padding_pos;  // offset 28 (4 bytes padding before dir to ensure
                         // 16-byte alignment for dir)
    glm::vec3 dir;       // offset 32 (12 bytes)
    float cut_off;       // offset 44 (4 bytes)
    float outer_cut_off; // offset 48 (4 bytes)
    float constant;      // offset 52 (4 bytes)
    float linear;        // offset 56 (4 bytes)
    float quadratic;     // offset 60 (4 bytes)
};
static_assert(
    sizeof(SpotLightStd140) == SHADER_SPOTLIGHT_STRUCT_SIZE,
    "SpotLightStd140 size mismatch"
);

// Structure for the entire UBO block
struct LightsUBOData {
    PointLightStd140 point_lights[SHADER_MAX_LIGHTS]; // offset 0
    DirectionalLightStd140
        dir_lights[SHADER_MAX_LIGHTS]; // offset SHADER_MAX_LIGHTS * 48
    SpotLightStd140
        spot_lights[SHADER_MAX_LIGHTS]; // offset SHADER_MAX_LIGHTS * (48 + 32)
    alignas(4
    ) int num_point_lights; // offset SHADER_MAX_LIGHTS * (48 + 32 + 64)
    alignas(4) int num_dir_lights;
    alignas(4) int num_spot_lights;
    // No explicit padding needed at the end if UBO_TOTAL_SIZE is met.
};
// Verify the total size against your macro.
// (50*48) + (50*32) + (50*64) + (3*4) = 2400 + 1600 + 3200 + 12 = 7212 bytes.
// Your UBO_SIZE macro correctly calculates this.
static_assert(
    sizeof(LightsUBOData) == UBO_TOTAL_SIZE, "LightsUBOData total size mismatch"
);

} // namespace shaders
} // namespace axolote
