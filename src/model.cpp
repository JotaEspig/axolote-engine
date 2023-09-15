#include <iostream>
#include <string>
#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <axolote/model.hpp>
#include <axolote/shader.hpp>
#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

Model::Model(const char *path, glm::vec3 _color)
{
    color = _color;
    load_model(path);
}

void Model::draw(Shader &shader, glm::mat4 matrix)
{
    for (auto e : meshes)
        e.draw(shader, matrix);
}

void Model::load_model(std::string path)
{
    Assimp::Importer import;

    const aiScene *scene = import.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ERROR::ASSIMP: " << import.GetErrorString() << std::endl;
        return;
    }

    directory = path.substr(0, path.find_last_of('/') + 1);
    process_node(scene->mRootNode, scene);
}

void Model::process_node(aiNode *node, const aiScene *scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(node->mChildren[i], scene);
}

Mesh Model::process_mesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<Vertex> vertices;
    std::vector<GLuint> indices;
    std::vector<Texture> textures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        vertex.position.x = mesh->mVertices[i].x;
        vertex.position.y = mesh->mVertices[i].y;
        vertex.position.z = mesh->mVertices[i].z; 

        vertex.color = color;

        if (mesh->mNormals != NULL)
        {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }
        else
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);

        if(mesh->mTextureCoords[0])
        {
            vertex.tex_UV.x = mesh->mTextureCoords[0][i].x; 
            vertex.tex_UV.y = 1-mesh->mTextureCoords[0][i].y;
        }
        else
            vertex.tex_UV = glm::vec2(0.0f, 0.0f);

        vertices.push_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
        std::vector<Texture> diffuse_texs =
            load_material_textures(mat, aiTextureType_DIFFUSE, "diffuse");
        textures.insert(textures.end(), diffuse_texs.begin(), diffuse_texs.end());
        std::vector<Texture> specular_texs =
            load_material_textures(mat, aiTextureType_SPECULAR, "specular");
        textures.insert(textures.end(), specular_texs.begin(), specular_texs.end());
    }

    return Mesh(vertices, indices, textures);
}

std::vector<Texture> Model::load_material_textures(aiMaterial *mat,
                                                   aiTextureType type,
                                                   std::string type_name)
{
    std::vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;
        for (unsigned int j = 0; j < loaded_textures.size(); ++j)
        {
            if (std::string(str.C_Str()) == loaded_textures_names[j])
            {
                skip = true;
                textures.push_back(loaded_textures[j]);
                break;
            }
        }

        if (skip)
            continue;

        Texture texture((directory + std::string(str.C_Str())).c_str(), type_name, i);
        loaded_textures.push_back(texture);
        loaded_textures_names.push_back(std::string(str.C_Str()));
        textures.push_back(texture);
    }
    return textures;
}

} // namespace axolote
