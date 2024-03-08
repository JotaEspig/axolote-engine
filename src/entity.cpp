#include <vector>

#include <glm/glm.hpp>

#include <axolote/entity.hpp>
#include <axolote/gl/shader.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/model.hpp>
#include <axolote/object3d.hpp>

#define UNUSED(x) (void)(x)

namespace axolote
{

Entity::Entity()
{
}

Entity::Entity(const Entity &ent) :
    objects{ent.objects}
{
}

Entity::Entity(Entity &&ent) :
    objects{std::move(ent.objects)}
{
}

void Entity::add_object(const Object3D &o)
{
    objects.push_back(o);
}

void Entity::add_object(const Object3D &o, const glm::mat4 &mat)
{
    size_t idx = objects.size();
    objects.push_back(o);
    set_matrix(idx, mat);
}

void Entity::set_matrix(size_t idx, const glm::mat4 &mat)
{
    assert(idx < objects.size());
    objects[idx].model_mat = mat;
}

void Entity::bind_shader_at(size_t idx, const gl::Shader &shader)
{
    assert(idx < objects.size());
    objects[idx].model->bind_shader(shader);
}

void Entity::update(double time)
{
    UNUSED(time);
}

void Entity::draw()
{
    for (size_t i = 0; i < objects.size(); ++i)
        objects[i].draw();
}

void Entity::draw(const glm::mat4 &mat)
{
    UNUSED(mat);
    draw();
}

void Entity::operator=(const Entity &ent)
{
    objects = ent.objects;
}

void Entity::operator=(Entity &&ent)
{
    objects = std::move(ent.objects);
}

} // namespace axolote
