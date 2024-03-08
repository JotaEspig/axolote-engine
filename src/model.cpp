#include <iostream>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include <axolote/assimp.hpp>
#include <axolote/gl/shader.hpp>
#include <axolote/gl/texture.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/model.hpp>

namespace axolote
{

Model::Model()
{
}

Model::Model(const Model &model) :
    meshes{model.meshes},
    color{model.color},
    loaded_textures{model.loaded_textures},
    loaded_textures_names{model.loaded_textures_names},
    directory{model.directory}
{
}

Model::Model(Model &&model) :
    meshes{std::move(model.meshes)},
    color{std::move(model.color)},
    loaded_textures{std::move(model.loaded_textures)},
    loaded_textures_names{std::move(model.loaded_textures_names)},
    directory{std::move(model.directory)}
{
}

Model::Model(
    const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
    const std::vector<gl::Texture> &textures
)
{
    meshes.push_back(GMesh{vertices, indices, textures});
}

Model::Model(std::string path, const glm::vec3 &_color) :
    color{_color}
{
    load_model(path);
}

void Model::bind_shader(const gl::Shader &shader)
{
    for (GMesh &e : meshes)
        e.bind_shader(shader);
};

void Model::draw()
{
    draw(glm::mat4(1.0f));
}

void Model::draw(const glm::mat4 &mat)
{
    for (GMesh e : meshes)
        e.draw(mat);
}

void Model::load_model(std::string path)
{
    Assimp::Importer import;

    const aiScene *scene
        = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE
        || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP: " << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/') + 1);
    process_node(
        scene->mRootNode, scene, meshes, color, loaded_textures,
        loaded_textures_names, directory
    );
}

void Model::operator=(const Model &model)
{
    color = model.color;
    meshes = model.meshes;
    loaded_textures = model.loaded_textures;
    loaded_textures_names = model.loaded_textures_names;
    directory = model.directory;
}

void Model::operator=(Model &&model)
{
    color = std::move(model.color);
    meshes = std::move(model.meshes);
    loaded_textures = std::move(model.loaded_textures);
    loaded_textures_names = std::move(model.loaded_textures_names);
    directory = std::move(model.directory);
}

} // namespace axolote
