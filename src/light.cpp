#include <glm/vec3.hpp>

#include "axolote/light.hpp"

#define UNUSED(x) (void)(x)

namespace axolote {

Light::Light(const glm::vec3 &color, bool is_set, Type type) :
  color{color},
  type{type} {
    render_state.is_paused = true;
    render_state.should_draw = is_set;
}

void Light::update(double absolute_time, double delta_time) {
    UNUSED(absolute_time);
    UNUSED(delta_time);
}

PointLight::PointLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
) :
  Light::Light{color, is_set, Type::Point},
  pos{pos},
  radius{radius} {
}

DirectionalLight::DirectionalLight(
    const glm::vec3 &color, bool is_set, const glm::vec3 &dir
) :
  Light::Light{color, is_set, Type::Directional},
  dir{dir} {
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

}
