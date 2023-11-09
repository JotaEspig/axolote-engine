#include <vector>

#include <axolote/mesh.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

Mesh::Mesh()
{
}

Mesh::Mesh(const Mesh &mesh) :
    vertices{mesh.vertices},
    indices{mesh.indices},
    textures{mesh.textures}
{
}

Mesh::Mesh(Mesh &&mesh) :
    vertices{mesh.vertices},
    indices{mesh.indices},
    textures{mesh.textures}
{
    mesh.vertices = std::vector<Vertex>{};
    mesh.indices = std::vector<GLuint>{};
    mesh.textures = std::vector<Texture>{};
}

Mesh::Mesh(const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices,
           const std::vector<Texture> &_textures) :
    vertices{_vertices},
    indices{_indices},
    textures{_textures}
{
}

void Mesh::operator=(const Mesh &mesh)
{
    vertices = mesh.vertices;
    indices = mesh.indices;
    textures = mesh.textures;
}

void Mesh::operator=(Mesh &&mesh)
{
    vertices = mesh.vertices;
    indices = mesh.indices;
    textures = mesh.textures;
    mesh.vertices = std::vector<Vertex>{};
    mesh.indices = std::vector<GLuint>{};
    mesh.textures = std::vector<Texture>{};
}

} // namespace axolote
