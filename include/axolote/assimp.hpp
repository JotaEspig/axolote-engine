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

#include <GL/gl.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/glm.hpp>

#include <axolote/gmesh.hpp>
#include <axolote/texture.hpp>

namespace axolote
{

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
void process_node(
    aiNode *node, const aiScene *scene, std::vector<GMesh> &meshes,
    glm::vec3 color, std::vector<Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
GMesh process_mesh(
    aiMesh *mesh, const aiScene *scene, glm::vec3 color,
    std::vector<Texture> loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

/**
 * \author João Vitor Espig (JotaEspig)
 * \date October 04, 2023
 * \version Octboer 04, 2023
 **/
std::vector<Texture> load_material_textures(
    aiMaterial *mat, aiTextureType type, std::string type_name,
    std::vector<Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
);

void process_node(
    aiNode *node, const aiScene *scene, std::vector<GMesh> &meshes,
    glm::vec3 color, std::vector<Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(process_mesh(
            mesh, scene, color, loaded_textures, loaded_textures_names,
            directory
        ));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
        process_node(
            node->mChildren[i], scene, meshes, color, loaded_textures,
            loaded_textures_names, directory
        );
}

GMesh process_mesh(
    aiMesh *mesh, const aiScene *scene, glm::vec3 color,
    std::vector<Texture> loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
)
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

        if (mesh->mTextureCoords[0])
        {
            vertex.tex_UV.x = mesh->mTextureCoords[0][i].x;
            vertex.tex_UV.y = 1 - mesh->mTextureCoords[0][i].y;
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

    aiMaterial *mat = scene->mMaterials[mesh->mMaterialIndex];
    std::vector<Texture> diffuse_texs = load_material_textures(
        mat, aiTextureType_DIFFUSE, "diffuse", loaded_textures,
        loaded_textures_names, directory
    );
    textures.insert(textures.end(), diffuse_texs.begin(), diffuse_texs.end());
    std::vector<Texture> specular_texs = load_material_textures(
        mat, aiTextureType_SPECULAR, "specular", loaded_textures,
        loaded_textures_names, directory
    );
    textures.insert(textures.end(), specular_texs.begin(), specular_texs.end());

    return GMesh(vertices, indices, textures);
}

std::vector<Texture> load_material_textures(
    aiMaterial *mat, aiTextureType type, std::string type_name,
    std::vector<Texture> &loaded_textures,
    std::vector<std::string> &loaded_textures_names, std::string directory
)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
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

        Texture texture(
            (directory + std::string(str.C_Str())).c_str(), type_name, i
        );
        loaded_textures.push_back(texture);
        loaded_textures_names.push_back(std::string(str.C_Str()));
        textures.push_back(texture);
    }
    return textures;
}

} // namespace axolote
