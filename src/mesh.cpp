#include <vector>

#include "axolote/mesh.hpp"
#include "axolote/structs.hpp"

namespace axolote {

Mesh::Mesh() {
}

Mesh::Mesh(
    const std::vector<Vertex> &_vertices, const std::vector<GLuint> &_indices,
    const std::vector<gl::Texture> &_textures
) :
  vertices{_vertices},
  indices{_indices},
  textures{_textures} {
}


} // namespace axolote
