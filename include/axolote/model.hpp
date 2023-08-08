#pragma once

#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <axolote/shader.hpp>
#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>

namespace axolote
{
    class Model
    {
    public:
        Model() = default;
        Model(const char *path);

        void draw(Shader &shader, glm::mat4 matrix = glm::mat4(1.0f));

    private:
        std::vector<Mesh> meshes;
        std::vector<Texture> loaded_textures;
        std::vector<std::string> loaded_textures_names;
        std::string directory;

        void load_model(std::string path);
        void process_node(aiNode *node, const aiScene *scene);
        Mesh process_mesh(aiMesh *mesh, const aiScene *scene);
        std::vector<Texture> load_material_textures(aiMaterial *mat,
                                                    aiTextureType type,
                                                    std::string type_name);
    };
}
