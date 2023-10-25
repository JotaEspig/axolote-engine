#include <iostream>
#include <vector>

#include <glm/glm.hpp>

#include <axolote/entity.hpp>
#include <axolote/model.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/shader.hpp>

namespace axolote
{

Entity::Entity()
{
}

void Entity::add_object(Object *o, const glm::mat4 &mat)
{
    objects.push_back(o);
    o->pos = mat;
}

void Entity::set_matrix(size_t idx, const glm::mat4 &mat)
{
    assert (idx < objects.size());
    objects[idx]->pos = mat;
}

void Entity::draw(Shader &shader)
{
    for (size_t i = 0; i < objects.size(); ++i)
        objects[i]->draw(shader);
}

} // namespace axolote
