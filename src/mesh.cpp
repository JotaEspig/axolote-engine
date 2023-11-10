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
    vertices{std::move(mesh.vertices)},
    indices{std::move(mesh.indices)},
    textures{std::move(mesh.textures)}
{
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
    vertices = std::move(mesh.vertices);
    indices = std::move(mesh.indices);
    textures = std::move(mesh.textures);
}

} // namespace axolote
