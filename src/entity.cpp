#include <vector>

#include <glm/glm.hpp>

#include <axolote/entity.hpp>
#include <axolote/model.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/shader.hpp>

#define UNUSED(x) (void)(x)

namespace axolote
{

Entity::Entity()
{
}

void Entity::add_object(const Object3D &o, const glm::mat4 &mat)
{
    size_t idx = objects.size();
    objects.push_back(o);
    set_matrix(idx, mat);
}

void Entity::set_matrix(size_t idx, const glm::mat4 &mat)
{
    assert (idx < objects.size());
    objects[idx].pos = mat;
}

void Entity::draw(Shader &shader)
{
    for (size_t i = 0; i < objects.size(); ++i)
        objects[i].draw(shader);
}

void Entity::draw(Shader &shader, const glm::mat4 &mat)
{
    UNUSED(mat);
    draw(shader);
}

} // namespace axolote
