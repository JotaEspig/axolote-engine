/**
 * @file instancing.hpp
 * @brief Instancing class header file
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
#pragma once

#include <unordered_map>

#include "axolote/drawable.hpp"
#include "axolote/gl/vbo.hpp"
#include "axolote/object3d.hpp"

namespace axolote {

class Instancing : public Drawable {
public:
    std::shared_ptr<Object3D> object;
    std::uint32_t element_count = 0;

    Instancing();
    Instancing(std::shared_ptr<Object3D> object);

    void add_instanced_mat4_array(
        const std::uint8_t location, const std::vector<glm::mat4> &data
    );
    void update_instanced_mat4_array(
        const std::uint8_t location, const std::vector<glm::mat4> &data
    );

    void bind_shader(std::shared_ptr<gl::Shader> shader) override;
    std::vector<std::shared_ptr<gl::Shader>> get_shaders() const override;
    void update(double dt) override;
    void draw() override;
    void draw(const glm::mat4 &mat) override;

private:
    std::unordered_map<std::uint8_t, std::shared_ptr<gl::VBO>>
        _instanced_array_vbos;
};

} // namespace axolote
