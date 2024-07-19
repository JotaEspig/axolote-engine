#include "axolote/light.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

Light::Light(const glm::vec3 &color, bool is_set, Type type) :
  color{color},
  is_set{is_set},
  type{type} {
}

void Light::bind(gl::Shader &shader, const std::string &prefix) {
    std::string color_name = prefix + ".color";
    shader.set_uniform_float3(color_name.c_str(), color.x, color.y, color.z);

    std::string is_set_name = prefix + ".is_set";
    shader.set_uniform_int(is_set_name.c_str(), is_set);
}

void Light::update(double dt) {
    UNUSED(dt);
}

PointLight::PointLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
) :
  Light::Light{color, is_set, Type::Point},
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

    std::string constant_name = prefix + ".constant";
    shader.set_uniform_float(constant_name.c_str(), constant);

    std::string linear_name = prefix + ".linear";
    shader.set_uniform_float(linear_name.c_str(), linear);

    std::string quadratic_name = prefix + ".quadratic";
    shader.set_uniform_float(quadratic_name.c_str(), quadratic);
}

DirectionalLight::DirectionalLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &dir
) :
  Light::Light{color, is_set, Type::Directional},
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
    const glm::vec3 &dir, float cut_off, float outer_cut_off
) :
  Light::Light{color, is_set, Type::Spot},
  pos{pos},
  dir{dir},
  cut_off{cut_off},
  outer_cut_off{outer_cut_off} {
}

void SpotLight::bind(gl::Shader &shader, const std::string &prefix) {
    // Base bindings
    Light::bind(shader, prefix);

    // Specific bindings
    std::string pos_name = prefix + ".pos";
    shader.set_uniform_float3(pos_name.c_str(), pos.x, pos.y, pos.z);

    std::string dir_name = prefix + ".dir";
    shader.set_uniform_float3(dir_name.c_str(), dir.x, dir.y, dir.z);

    std::string cut_off_name = prefix + ".cut_off";
    shader.set_uniform_float(cut_off_name.c_str(), cut_off);

    std::string outer_cut_off_name = prefix + ".outer_cut_off";
    shader.set_uniform_float(outer_cut_off_name.c_str(), outer_cut_off);

    std::string constant_name = prefix + ".constant";
    shader.set_uniform_float(constant_name.c_str(), constant);

    std::string linear_name = prefix + ".linear";
    shader.set_uniform_float(linear_name.c_str(), linear);

    std::string quadratic_name = prefix + ".quadratic";
    shader.set_uniform_float(quadratic_name.c_str(), quadratic);
}

}
