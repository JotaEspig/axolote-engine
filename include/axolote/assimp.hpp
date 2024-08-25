/**
 * @file assimp.hpp
 * @brief assimp functions
 * @author João Vitor Espig (jotaespig@gmail.com)
 *
 * This file is a piece of shit.
 * This file is created to try to don't force the user to have the assimp
 *header. to run the library.
 * TODO
 * Try to find a better solution than this.
 **/
#pragma once

#include <memory>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "axolote/gl/texture.hpp"
#include "axolote/mesh.hpp"

namespace axolote {

/**
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
void process_node(
    aiNode *node, const aiScene *scene, std::vector<Mesh> &meshes,
    glm::vec4 color, std::vector<std::shared_ptr<gl::Texture>> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
Mesh process_mesh(
    aiMesh *mesh, const aiScene *scene, glm::vec4 color,
    std::vector<std::shared_ptr<gl::Texture>> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * @author João Vitor Espig (jotaespig@gmail.com)
 **/
std::vector<std::shared_ptr<gl::Texture>> load_material_textures(
    aiMaterial *mat, aiTextureType type, std::string type_name,
    std::vector<std::shared_ptr<gl::Texture>> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

} // namespace axolote
