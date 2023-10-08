#include <GL/gl.h>
#include <glm/glm.hpp>

#include <axolote/object2d.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

Object2D::Object2D()
{
}

Object2D::Object2D(std::vector<Vertex> vertices, std::vector<GLuint> indices,
                   std::vector<Texture> textures, glm::mat4 mat) :
    GMesh::GMesh(vertices, indices, textures)
{
    pos = mat;
}

void Object2D::draw(Shader &shader)
{
    GMesh::draw(shader, pos);
}

} // namespace axolote
