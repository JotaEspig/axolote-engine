#pragma once

#include <vector>

#include <glm/glm.hpp>

#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>

namespace axolote
{ 

enum class EntityType
{
    MODEL,
    MESH
};

class Entity
{
    EntityType type;
    std::vector<Model> models;
    std::vector<Mesh> meshes;
    std::vector<glm::mat4> matrices;

public:
    Entity();
    void set_matrix(size_t idx, glm::mat4 mat = glm::mat4(1.0f));
    void draw(Shader shader);
    void add_model(Model m, glm::mat4 mat = glm::mat4(1.0f));
    void add_mesh(Mesh m, glm::mat4 mat = glm::mat4(1.0f));
};

} // namespace axolote
