#pragma once

#include <memory>
#include <string>

#include "axolote/drawable.hpp"
#include "axolote/gl/cubemap.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/gl/vao.hpp"
#include "axolote/gl/vbo.hpp"

namespace axolote {

class Skybox : public Drawable {
public:
    /**
     * @brief Creates a skybox
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param texture_faces_filenames array of 6 strings with the paths to the
     * textures (front, back, left, right, top, bottom)
     **/
    Skybox(std::string texture_faces_filenames[6]);
    /**
     * @brief Creates a skybox
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param texture_faces_folder_path path to the folder containing the 6
     * textures (front, back, left, right, top, bottom)
     *
     * Search automatically for the textures in the folder. The textures must be
     * named as follows:
     * front(.png/jpg), back(.png/jpg), left(.png/jpg), right(.png/jpg),
     * top(.png/jpg), bottom(.png/jpg)
     **/
    Skybox(std::string texture_faces_folder_path);

    /**
     * @brief virtual function bind_shader
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind_shader(std::shared_ptr<gl::Shader> shader) override;
    /**
     * @brief virtual function get_shader
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    std::vector<std::shared_ptr<gl::Shader>> get_shaders() const override;
    /**
     * @brief virtual function update
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void update(double absolute_time, double delta_time) override;
    /**
     * @brief virtual function draw
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void draw() override;
    /**
     * @brief virtual function draw using a matrix 4x4 as the model matrix
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void draw(const glm::mat4 &mat) override;

private:
    std::shared_ptr<gl::VAO> _vao;
    std::shared_ptr<gl::VBO> _vbo;
    std::shared_ptr<gl::Cubemap> _cubemap;
    std::shared_ptr<gl::Shader> _shader;

    Skybox();
};

}
