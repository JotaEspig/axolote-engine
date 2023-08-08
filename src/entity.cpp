#include <axolote/entity.hpp>
#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>

using namespace axolote;

Entity::Entity()
{
}

void Entity::set_matrix(glm::mat4 mat)
{
    matrix = mat;
}

void Entity::draw(Shader shader)
{
    if (type == EntityType::MODEL)
        model.draw(shader, matrix);
    else if (type == EntityType::MESH)
        mesh.draw(shader, matrix);
}

void Entity::set_model(Model m)
{
    type = EntityType::MODEL;
    model = m;
}

void Entity::set_mesh(Mesh m)
{
    type = EntityType::MESH;
    mesh = m;
}
