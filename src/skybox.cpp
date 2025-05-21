#include <filesystem>
#include <string>
#include <vector>
#include <stdexcept>

#include <stb/stb_image.h>

#include "axolote/gl/cubemap.hpp"
#include "axolote/gl/shader.hpp"
#include "axolote/skybox.hpp"
#include "axolote/utils.hpp"

#define UNUSED(x) (void)(x)

std::string shader_vert_source = R"(
#version 330 core
layout (location = 0) in vec3 aPos;

const float INVERSE_SQRT3 = 0.5773502692;

out vec3 TexCoords;

uniform mat4 axolote_scene_camera;
uniform vec3 axolote_camera_pos;
uniform float axolote_scene_camera_max_dist;

void main()
{
    mat4 model = mat4(1.0f);
    float distance = axolote_scene_camera_max_dist * INVERSE_SQRT3;
    model[0][0] = distance;
    model[1][1] = distance;
    model[2][2] = distance;
    model[3] = vec4(axolote_camera_pos, 1.0f);

    vec3 curr_pos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aPos;
    gl_Position = axolote_scene_camera * vec4(curr_pos, 1.0);
}
)";

std::string shader_frag_source = R"(
#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform samplerCube skybox;

void main()
{    
    FragColor = texture(skybox, TexCoords);
}
)";

std::vector<float> skybox_vertices = {
    // positions
    -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  -1.0f,
    -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f, 1.0f,

    1.0f,  -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f,

    -1.0f, -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f, -1.0f, 1.0f,

    -1.0f, 1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  1.0f,
    1.0f,  1.0f,  1.0f,  -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f,  -1.0f,

    -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, -1.0f,
    1.0f,  -1.0f, -1.0f, -1.0f, -1.0f, 1.0f,  1.0f,  -1.0f, 1.0f
};

namespace axolote {

Skybox::Skybox(std::string texture_faces_filenames[6]) :
  Skybox{} {
    stbi_set_flip_vertically_on_load(false);
    _cubemap = gl::Cubemap::create(texture_faces_filenames);
    _cubemap->bind();
}

Skybox::Skybox(std::string texture_faces_folder_path) :
  Skybox{} {
    stbi_set_flip_vertically_on_load(false);
    std::string texture_faces_filenames[6];
    texture_faces_filenames[0] = texture_faces_folder_path + "/right.jpg";
    texture_faces_filenames[1] = texture_faces_folder_path + "/left.jpg";
    texture_faces_filenames[2] = texture_faces_folder_path + "/top.jpg";
    texture_faces_filenames[3] = texture_faces_folder_path + "/bottom.jpg";
    texture_faces_filenames[4] = texture_faces_folder_path + "/front.jpg";
    texture_faces_filenames[5] = texture_faces_folder_path + "/back.jpg";
    for (int i = 0; i < 6; i++) {
        if (!std::filesystem::exists(texture_faces_filenames[i])) {
            // change the extension to png
            std::string new_filename = texture_faces_filenames[i];
            new_filename.replace(
                new_filename.find_last_of('.'), std::string::npos, ".png"
            );
            if (std::filesystem::exists(new_filename)) {
                texture_faces_filenames[i] = new_filename;
            }
            else {
                debug(
                    DebugType::FATAL, "Skybox texture not found: %s",
                    texture_faces_filenames[i].c_str()
                );
                throw std::runtime_error(
                    "Skybox texture not found: " + texture_faces_filenames[i]
                );
            }
        }
    }

    _cubemap = gl::Cubemap::create(texture_faces_filenames);
    _cubemap->bind();
}

void Skybox::bind_shader(std::shared_ptr<gl::Shader> shader) {
    _shader = shader;
}

std::vector<std::shared_ptr<gl::Shader>> Skybox::get_shaders() const {
    return {_shader};
}

void Skybox::update(double absolute_time, double delta_time) {
    UNUSED(absolute_time);
    UNUSED(delta_time);
}

void Skybox::draw() {
    glDepthFunc(GL_LEQUAL);

    glDisable(GL_CULL_FACE);

    _shader->use();
    _shader->set_uniform_int("skybox", 0);
    _vao->bind();
    _cubemap->bind();
    glDrawArrays(GL_TRIANGLES, 0, 36);
    _vao->unbind();
    _cubemap->unbind();

    // todo enable if needed
    glEnable(GL_CULL_FACE);

    glDepthFunc(GL_LESS);
}

void Skybox::draw(const glm::mat4 &mat) {
    UNUSED(mat);
    draw();
}

Skybox::Skybox() :
  _shader{gl::Shader::create_from_source_code(
      shader_vert_source.c_str(), shader_frag_source.c_str()
  )} {
    _vao = gl::VAO::create();
    _vao->bind();
    _vbo = gl::VBO::create(skybox_vertices);
    _vbo->bind();
    _vao->link_attrib(_vbo, 0, 3, GL_FLOAT, 3 * sizeof(float), (void *)0);
    _vao->unbind();
    _vbo->unbind();
}

} // namespace axolote
