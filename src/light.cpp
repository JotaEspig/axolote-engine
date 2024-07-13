#include "axolote/light.hpp"

namespace axolote {

Light::Light(const glm::vec3 &color, bool is_set, Type type) :
  color{color},
  is_set{is_set}, type{type} {
}

void Light::bind(gl::Shader &shader, const std::string &prefix) {
    std::string color_name = prefix + ".color";
    shader.set_uniform_float3(color_name.c_str(), color.x, color.y, color.z);

    std::string is_set_name = prefix + ".is_set";
    shader.set_uniform_int(is_set_name.c_str(), is_set);
}

PointLight::PointLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
) :
  Light::Light{color, is_set, Type::point},
  pos{pos},
  radius{radius} {
}

void PointLight::bind(gl::Shader &shader, const std::string &prefix) {
    // Base bindings
    Light::bind(shader, prefix);

    // Specific bindings
    std::string pos_name = prefix + ".pos";
    shader.set_uniform_float3(pos_name.c_str(), pos.x, pos.y, pos.z);

    std::string radius_name = prefix + ".radius";
    shader.set_uniform_float(radius_name.c_str(), radius);
}

DirectionalLight::DirectionalLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &dir
) :
  Light::Light{color, is_set, Type::directional},
  dir{dir} {
}

void DirectionalLight::bind(gl::Shader &shader, const std::string &prefix) {
    // Base bindings
    Light::bind(shader, prefix);

    // Specific bindings
    std::string dir_name = prefix + ".dir";
    shader.set_uniform_float3(dir_name.c_str(), dir.x, dir.y, dir.z);
}

SpotLight::SpotLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &pos,
    const glm::vec3 &dir, float cut_off_angle
) :
  Light::Light{color, is_set, Type::spot},
  pos{pos},
  dir{dir},
  cut_off_angle{cut_off_angle} {
}

void SpotLight::bind(gl::Shader &shader, const std::string &prefix) {
    // Base bindings
    Light::bind(shader, prefix);

    // Specific bindings
    std::string pos_name = prefix + ".pos";
    shader.set_uniform_float3(pos_name.c_str(), pos.x, pos.y, pos.z);

    std::string dir_name = prefix + ".dir";
    shader.set_uniform_float3(dir_name.c_str(), dir.x, dir.y, dir.z);

    std::string cut_off_angle_name = prefix + ".cut_off_angle";
    shader.set_uniform_float(cut_off_angle_name.c_str(), cut_off_angle);
}

}