#include <vector>

#include <axolote/mesh.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

Mesh::Mesh(std::vector<Vertex> _vertices, std::vector<GLuint> _indices,
           std::vector<Texture> _textures) :
    vertices{_vertices},
    indices{_indices},
    textures{_textures}
{
}

} // namespace axolote
