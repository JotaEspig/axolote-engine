/**
 * \file light.hpp
 * \brief Light classes
 * \author Mickael Reichert (mickaelrei)
 **/
#pragma once

#include <string>

#include "axolote/gl/shader.hpp"

namespace axolote {

/**
 * \brief Light class
 * \author Mickael Reichert (mickaelrei)
 **/
class Light {
public:
    /**
     * \brief Light type
     * \author Mickael Reichert (mickaelrei)
     **/
    enum class Type {
        point,
        directional,
        spot,
    };

    /**
     * \brief Constructor
     * \author Mickael Reichert (mickaelrei)
     **/
    Light(const glm::vec3 &color, bool is_set, Type type);

    /**
     * \brief Bind light to shader
     * \author Mickael Reichert (mickaelrei)
     **/
    virtual void bind(gl::Shader &shader, const std::string &prefix);

    /** Light color **/
    glm::vec3 color;
    /** Light is set **/
    bool is_set;

    /** Light type **/
    Type type;
};

/**
 * \brief Point light class
 * \author Mickael Reichert (mickaelrei)
 **/
class PointLight : public Light {
public:
    /**
     * \brief Constructor
     * \author Mickael Reichert (mickaelrei)
     **/
    PointLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
    );

    /**
     * \brief Bind light to shader
     * \author Mickael Reichert (mickaelrei)
     **/
    void bind(gl::Shader &shader, const std::string &prefix) override;

    /** Light position **/
    glm::vec3 pos;
    /** Light radius **/
    float radius;
};

/**
 * \brief Directional light class
 * \author Mickael Reichert (mickaelrei)
 **/
class DirectionalLight : public Light {
public:
    /**
     * \brief Constructor
     * \author Mickael Reichert (mickaelrei)
     **/
    DirectionalLight(const glm::vec3 &color, bool is_set, const glm::vec3 &dir);

    /**
     * \brief Bind light to shader
     * \author Mickael Reichert (mickaelrei)
     **/
    void bind(gl::Shader &shader, const std::string &prefix) override;

    /** Light direction **/
    glm::vec3 dir;
};

/**
 * \brief Spot light class
 * \author Mickael Reichert (mickaelrei)
 **/
class SpotLight : public Light {
public:
    /**
     * \brief Constructor
     * \author Mickael Reichert (mickaelrei)
     **/
    SpotLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos,
        const glm::vec3 &dir, float cut_off_angle
    );

    /**
     * \brief Bind light to shader
     * \author Mickael Reichert (mickaelrei)
     **/
    void bind(gl::Shader &shader, const std::string &prefix) override;

    /** Light position **/
    glm::vec3 pos;
    /** Light direction **/
    glm::vec3 dir;
    /** Light cut off angle **/
    float cut_off_angle;
};

} // namespace axolote
