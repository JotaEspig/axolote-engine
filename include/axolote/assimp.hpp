/**
 * \file assimp.hpp
 * \brief assimp functions
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version October 04, 2023
 *
 * This file is a piece of shit.
 * This file is created to try to don't force the user to have the assimp
 *header. to run the library.
 * TODO
 * Try to find a better solution than this.
 **/
#pragma once

#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include "axolote/glad/glad.h"
#include "axolote/gl/texture.hpp"
#include "axolote/mesh.hpp"

namespace axolote {

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
void process_node(
    aiNode *node, const aiScene *scene, std::vector<Mesh> &meshes,
    glm::vec3 color, std::vector<gl::Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
Mesh process_mesh(
    aiMesh *mesh, const aiScene *scene, glm::vec3 color,
    std::vector<gl::Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
std::vector<gl::Texture> load_material_textures(
    aiMaterial *mat, aiTextureType type, std::string type_name,
    std::vector<gl::Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

} // namespace axolote
