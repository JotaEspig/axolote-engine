#include <iostream>
#include <vector>

#include <axolote/entity.hpp>
#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>

using namespace axolote;

Entity::Entity()
{
}

void Entity::set_matrix(size_t idx, glm::mat4 mat)
{
    if (idx >= matrices.size())
        std::cerr << "Entity: invalid index for matrix setting" << std::endl;
    matrices[idx] = mat;
}

void Entity::draw(Shader shader)
{
    if (type == EntityType::MODEL)
    {
        for (size_t i = 0; i < models.size(); ++i)
            models[i].draw(shader, matrices[i]);
    }
    else if (type == EntityType::MESH)
    {
        glDisable(GL_CULL_FACE);
        for (size_t i = 0; i < meshes.size(); ++i)
            meshes[i].draw(shader, matrices[i]);

        glEnable(GL_CULL_FACE);
    }
}

void Entity::add_model(Model m, glm::mat4 mat)
{
    type = EntityType::MODEL;
    models.push_back(m);
    matrices.push_back(mat);
}

void Entity::add_mesh(Mesh m, glm::mat4 mat)
{
    type = EntityType::MESH;
    meshes.push_back(m);
    matrices.push_back(mat);
}
