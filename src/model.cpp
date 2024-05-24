#include <iostream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include <axolote/assimp.hpp>
#include <axolote/gl/shader.hpp>
#include <axolote/gl/texture.hpp>
#include <axolote/mesh.hpp>
#include <axolote/model.hpp>

namespace axolote {

Model::Model() {
}

Model::Model(std::string path, const glm::vec3 &color) {
    load_model(path, color);
}

void Model::load_model(std::string path, const glm::vec3 &color) {
    meshes.clear();

    std::vector<gl::Texture> loaded_textures;
    std::vector<std::string> loaded_textures_names;

    Assimp::Importer import;

    const aiScene *scene
        = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    bool error = !scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
                 || !scene->mRootNode;
    if (error) {
        std::cerr << "ERROR::ASSIMP: " << import.GetErrorString() << std::endl;
        return;
    }

    std::string directory = path.substr(0, path.find_last_of('/') + 1);
    process_node(
        scene->mRootNode, scene, meshes, color, loaded_textures,
        loaded_textures_names, directory
    );
}

} // namespace axolote
