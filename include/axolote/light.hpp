#pragma once

#include <string>

#include "axolote/gl/shader.hpp"

namespace axolote {

class Light {
public:
    enum class Type {
        point,
        directional,
        spot,
    };

    Light(const glm::vec3 &color, bool is_set, Type type);

    virtual void bind(gl::Shader &shader, const std::string &prefix);

    glm::vec3 color;
    bool is_set;

    Type type;
};

class PointLight : public Light {
public:
    PointLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
    );

    void bind(gl::Shader &shader, const std::string &prefix) override;

    glm::vec3 pos;
    float radius;
};

class DirectionalLight : public Light {
public:
    DirectionalLight(const glm::vec3 &color, bool is_set, const glm::vec3 &dir);

    void bind(gl::Shader &shader, const std::string &prefix) override;

    glm::vec3 dir;
};

class SpotLight : public Light {
public:
    SpotLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos,
        const glm::vec3 &dir, float cut_off_angle
    );

    void bind(gl::Shader &shader, const std::string &prefix) override;

    glm::vec3 pos;
    glm::vec3 dir;
    float cut_off_angle;
};

} // namespace axolote