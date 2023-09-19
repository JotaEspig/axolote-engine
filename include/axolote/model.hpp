#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>

#include <axolote/shader.hpp>
#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

class Model
{
public:
    Model() = default;
    Model(const char *path, glm::vec3 _color = glm::vec3(0.0f, 0.0f, 0.0f));

    void draw(Shader &shader, glm::mat4 matrix = glm::mat4(1.0f));

private:
    glm::vec3 color;
    std::vector<Mesh> meshes;
    std::vector<Texture> loaded_textures;
    std::vector<std::string> loaded_textures_names;
    std::string directory;

    void load_model(std::string path);
};

} // namespace axolote
