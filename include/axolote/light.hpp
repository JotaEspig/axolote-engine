/**
 * @file light.hpp
 * @brief Light classes
 * @author Mickael Reichert (mickael.reichert@gmail.com)
 **/
#pragma once

#include <memory>
#include <string>

#include "axolote/gl/shader.hpp"

namespace axolote {

/**
 * @brief Light class
 * @author Mickael Reichert (mickael.reichert@gmail.com)
 **/
class Light {
public:
    /**
     * @brief Light type
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    enum class Type {
        Point,
        Directional,
        Spot,
    };

    /**
     * @brief Constructor
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    Light(const glm::vec3 &color, bool is_set, Type type);

    /**
     * @brief Bind light to shader
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    virtual void
    bind(std::shared_ptr<gl::Shader> shader, const std::string &prefix);
    /**
     * @brief Update light
     * @author João Vitor Espig
     **/
    virtual void update(double dt);

    /** Light color **/
    glm::vec3 color;
    /** Light is set **/
    bool is_set;

    /** Light type **/
    Type type;
};

/**
 * @brief Point light class
 * @author Mickael Reichert (mickael.reichert@gmail.com)
 **/
class PointLight : public Light {
public:
    /** Light position **/
    glm::vec3 pos;
    /** Light radius **/
    float radius;
    /** Light constant term **/
    float constant = 1.0f;
    /** Light linear term **/
    float linear = 0.09f;
    /** Light quadratic term **/
    float quadratic = 0.032f;

    /**
     * @brief Constructor
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    PointLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos, float radius
    );

    /**
     * @brief Bind light to shader
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    void bind(std::shared_ptr<gl::Shader> shader, const std::string &prefix)
        override;
};

/**
 * @brief Directional light class
 * @author Mickael Reichert (mickael.reichert@gmail.com)
 **/
class DirectionalLight : public Light {
public:
    /** Light direction **/
    glm::vec3 dir;
    /** Light intensity **/
    float intensity = 1.0f;

    /**
     * @brief Constructor
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    DirectionalLight(const glm::vec3 &color, bool is_set, const glm::vec3 &dir);

    /**
     * @brief Bind light to shader
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    void bind(std::shared_ptr<gl::Shader> shader, const std::string &prefix)
        override;
};

/**
 * @brief Spot light class
 * @author Mickael Reichert (mickael.reichert@gmail.com)
 **/
class SpotLight : public Light {
public:
    /** Light position **/
    glm::vec3 pos;
    /** Light direction **/
    glm::vec3 dir;
    /** Light cut off angle **/
    float cut_off;
    /** Light outer cut off **/
    float outer_cut_off;
    /** Light constant term **/
    float constant = 1.0f;
    /** Light linear term **/
    float linear = 0.09f;
    /** Light quadratic term **/
    float quadratic = 0.032f;

    /**
     * @brief Constructor
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    SpotLight(
        const glm::vec3 &color, bool is_set, const glm::vec3 &pos,
        const glm::vec3 &dir, float cut_off_angle, float outer_cut_off_angle
    );

    /**
     * @brief Bind light to shader
     * @author Mickael Reichert (mickael.reichert@gmail.com)
     **/
    void bind(std::shared_ptr<gl::Shader> shader, const std::string &prefix)
        override;
};

} // namespace axolote
