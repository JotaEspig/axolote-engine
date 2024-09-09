/**
 * @file grid.hpp
 * @brief Grid class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <cstdint>
#include <memory>
#include <vector>

#include <glm/fwd.hpp>

#include "axolote/drawable.hpp"
#include "axolote/gl/ebo.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gl/vao.hpp"
#include "axolote/gl/vbo.hpp"

namespace axolote {

namespace utils {

/**
 * @brief Grid class
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
class Grid : public Drawable {
public:
    /** is 3D grid **/
    bool is_3d = false;
    /** grid size **/
    std::uint8_t size = 10;
    /** grid build mesh step **/
    std::uint8_t step = 1;
    /** fading factor **/
    float fading_factor = 30.0f;
    /** grid color **/
    glm::vec4 color{1.0f};
    /** camera pos **/
    glm::vec3 camera_pos{0.0f, 0.0f, 0.0f};
    /** grid position **/
    glm::vec3 pos{0.0f};
    /** model_mat **/
    glm::mat4 model_mat{1.0f};

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Grid();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param size grid size
     * @param step grid step
     * @param is_3d is 3D grid
     * @param color grid color
     **/
    Grid(
        std::uint8_t size, std::uint8_t step, bool is_3d, const glm::vec4 &color
    );

    /**
     * @brief build the mesh for the grid
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void build_mesh();
    void bind_shader(std::shared_ptr<gl::Shader> shader_program) override;
    std::vector<std::shared_ptr<gl::Shader>> get_shaders() const override;
    void update(double delta_t) override;
    void draw() override;
    void draw(const glm::mat4 &mat) override;

private:
    std::shared_ptr<gl::VAO> _vao;
    std::shared_ptr<gl::VBO> _vbo;
    std::shared_ptr<gl::EBO> _ebo;
    /** shader program **/
    std::shared_ptr<gl::Shader> _shader;
};

} // namespace utils

} // namespace axolote
