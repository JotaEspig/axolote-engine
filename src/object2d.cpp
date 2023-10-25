#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object2d.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>

#define UNUSED(x) (void)(x)

namespace axolote
{

Object2D::Object2D()
{
}

Object2D::Object2D(const glm::mat4 &mat,
                   const std::vector<Vertex> &vertices,
                   const std::vector<GLuint> &indices,
                   const std::vector<Texture> &textures) :
    GMesh::GMesh(vertices, indices, textures)
{
    pos = mat;
}

void Object2D::draw(Shader &shader)
{
    GMesh::draw(shader, pos);
}

void Object2D::draw(Shader &shader, const glm::mat4 &mat)
{
    UNUSED(mat);
    draw(shader);
}

} // namespace axolote
