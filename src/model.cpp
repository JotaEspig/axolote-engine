#include <string>
#include <vector>
#include <stdexcept>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <json/json.hpp>

#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>
#include <axolote/utils.hpp>

using namespace axolote;
using json = nlohmann::json;

Model::Model(const char *_filename)
{
    filename = _filename;

    std::string json_raw_text = get_file_content(_filename);
    json_obj = json::parse(json_raw_text);
    data = get_data();

    // traverse all nodes
    traverse_node(0);
}

void Model::draw(Shader &shader)
{
    for (size_t i = 0; i < meshes.size(); i++)
    {
        meshes[i].draw(shader, matrices_meshes[i]);
    }
}

void Model::load_mesh(unsigned int ind_mesh)
{
    unsigned int ind_acc_ind = json_obj["meshes"][ind_mesh]["primitives"][0]["indices"];
    unsigned int pos_acc_ind = json_obj["meshes"][ind_mesh]["primitives"][0]["attributes"]["POSITION"];
    unsigned int tex_acc_ind = json_obj["meshes"][ind_mesh]["primitives"][0]["attributes"]["TEXCOORD_0"];
    unsigned int normal_acc_ind = json_obj["meshes"][ind_mesh]["primitives"][0]["attributes"]["NORMAL"];

    std::vector<float> pos_vec = get_floats(json_obj["accessors"][pos_acc_ind]);
    std::vector<float> tex_vec = get_floats(json_obj["accessors"][tex_acc_ind]);
    std::vector<float> normal_vec = get_floats(json_obj["accessors"][normal_acc_ind]);
    std::vector<glm::vec3> positions = group_floats_vec3(pos_vec);
    std::vector<glm::vec2> tex_UVs = group_floats_vec2(tex_vec);
    std::vector<glm::vec3> normals = group_floats_vec3(normal_vec);

    std::vector<Vertex> vertices = assemble_vertices(positions, tex_UVs, normals);
    std::vector<GLuint> indices = get_indices(json_obj["accessors"][ind_acc_ind]);
    std::vector<Texture> textures = get_textures();

    Mesh m = Mesh(vertices, indices, textures);
    meshes.push_back(m);
}

void Model::traverse_node(unsigned int next_node, glm::mat4 matrix)
{
    json node = json_obj["nodes"][next_node];

    glm::vec3 translation = glm::vec3(0.0f, 0.0f, 0.0f);
    if (node.find("translation") != node.end())
    {
        float trans_values[3];
        for (size_t i = 0; i < node["translation"].size(); i++)
            trans_values[i] = node["translation"][i];
        translation = glm::make_vec3(trans_values);
    }

    glm::quat rotation = glm::quat(1.0f, 0.0f, 0.0f, 0.0f);
    if (node.find("rotation") != node.end())
    {
        float rot_values[] = {
            node["rotation"][3],
            node["rotation"][0],
            node["rotation"][1],
            node["rotation"][2]
        };
        rotation = glm::make_quat(rot_values);
    }

    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);
    if (node.find("scale") != node.end())
    {
        float scale_values[3];
        for (size_t i = 0; i < node["scale"].size(); i++)
            scale_values[i] = node["scale"][i];
        scale = glm::make_vec3(scale_values);
    }

    glm::mat4 mat_node = glm::mat4(1.0f);
    if (node.find("matrix") != node.end())
    {
        float mat_values[16];
        for (size_t i = 0; i < node["matrix"].size(); i++)
            mat_values[i] = node["matrix"][i];

        mat_node = glm::make_mat4(mat_values);
    }

    glm::mat4 trans = glm::mat4(1.0f);
    glm::mat4 rot = glm::mat4(1.0f);
    glm::mat4 sca = glm::mat4(1.0f);
    trans = glm::translate(trans, translation);
    rot = glm::mat4_cast(rotation);
    sca = glm::scale(sca, scale);

    glm::mat4 mat_next_node = matrix * mat_node * trans * rot * sca;

    if (node.find("mesh") != node.end())
    {
        translations_meshes.push_back(translation);
        rotations_meshes.push_back(rotation);
        scales_meshes.push_back(scale);
        matrices_meshes.push_back(mat_next_node);

        load_mesh(node["mesh"]);
    }

    if (node.find("children") != node.end())
    {
        for (size_t i = 0; i < node["children"].size(); i++)
            traverse_node(node["children"][i], mat_next_node);
    }
}

std::vector<unsigned char> Model::get_data()
{
    std::string bytes_text;
    std::string uri = json_obj["buffers"][0]["uri"];

    std::string file_str = std::string(filename);
    std::string file_dir = file_str.substr(0, file_str.find_last_of('/') + 1);
    bytes_text = get_file_content((file_dir + uri).c_str());

    std::vector<unsigned char> _data(bytes_text.begin(), bytes_text.end());
    return _data;
}

std::vector<float> Model::get_floats(json accessor)
{
    std::vector<float> floats;

    unsigned int buff_view_ind = accessor.value("bufferView", 1);
    unsigned int count = accessor["count"];
    unsigned int acc_byte_offset = accessor.value("byteOffset", 0);
    std::string type = accessor["type"];
    
    json buffer_view = json_obj["bufferViews"][buff_view_ind];
    unsigned int byte_offset = buffer_view["byteOffset"];

    unsigned int num_per_vert;
    if (type == "SCALAR")
        num_per_vert = 1;
    else if (type == "VEC2")
        num_per_vert = 2;
    else if (type == "VEC3")
        num_per_vert = 3;
    else if (type == "VEC4")
        num_per_vert = 4;
    else
        throw std::invalid_argument("type is invalid (not SCALAR, VEC2, VEC3 or VEC4)");

    unsigned int beginning_of_data = byte_offset + acc_byte_offset;
    unsigned int length_of_data = count * 4 * num_per_vert;
    for (unsigned int i = beginning_of_data; i < beginning_of_data + length_of_data;)
    {
        unsigned char bytes[] {data[i++], data[i++], data[i++], data[i++]};
        float value;
        std::memcpy(&value, bytes, sizeof(float));
        floats.push_back(value);
    }

    return floats;
}

std::vector<GLuint> Model::get_indices(json accessor)
{
    std::vector<GLuint> indices;

    unsigned int buff_view_ind = accessor.value("bufferView", 0);
    unsigned int count = accessor["count"];
    unsigned int acc_byte_offset = accessor.value("byteOffset", 0);
    unsigned int component_type = accessor["componentType"];

    json buffer_view = json_obj["bufferViews"][buff_view_ind];
    unsigned int byte_offset = buffer_view["byteOffset"];

    unsigned int beginning_of_data = byte_offset + acc_byte_offset;
    if (component_type == 5125)
    {
        for (unsigned int i = beginning_of_data; i < byte_offset + acc_byte_offset + count * 4;)
        {
            unsigned char bytes[] = {data[i++], data[i++], data[i++], data[i++]};
            unsigned int value;
            std::memcpy(&value, bytes, sizeof(unsigned int));
            indices.push_back((GLuint)value);
        }
    }
    else if (component_type == 5123)
    {
        for (unsigned int i = beginning_of_data; i < byte_offset + acc_byte_offset + count * 2;)
        {
            unsigned char bytes[] = {data[i++], data[i++]};
            unsigned short value;
            std::memcpy(&value, bytes, sizeof(unsigned short));
            indices.push_back((GLuint)value);
        }
    }
    else if (component_type == 5122)
    {
        for (unsigned int i = beginning_of_data; i < byte_offset + acc_byte_offset + count * 2;)
        {
            unsigned char bytes[] = {data[i++], data[i++]};
            short value;
            std::memcpy(&value, bytes, sizeof(short));
            indices.push_back((GLuint)value);
        }
    }

    return indices;
}

std::vector<Texture> Model::get_textures()
{
    std::vector<Texture> textures;

    std::string file_str = std::string(filename);
    std::string file_dir = file_str.substr(0, file_str.find_last_of('/') + 1);

    for (size_t i = 0; i < json_obj["images"].size(); i++)
    {
        std::string tex_path = json_obj["images"][i]["uri"];

        bool skip = false;
        for (unsigned int j = 0; j < loaded_tex_name.size(); j++)
        {
            if (loaded_tex_name[j] == tex_path)
            {
                textures.push_back(loaded_tex[j]);
                skip = true;
                break;
            }
        }

        if (skip)
            continue;

        Texture tex;
        if (tex_path.find("baseColor") != std::string::npos)
        {
            tex = Texture((file_dir + tex_path).c_str(), "diffuse", loaded_tex.size());
        }
        else if (tex_path.find("metallicRoughness") != std::string::npos)
        {
            tex = Texture((file_dir + tex_path).c_str(), "specular", loaded_tex.size());
        }

        if (!tex.loaded)
            continue;

        textures.push_back(tex);
        loaded_tex.push_back(tex);
        loaded_tex_name.push_back(tex_path);
    }

    return textures;
}

std::vector<Vertex> Model::assemble_vertices(std::vector<glm::vec3> pos,
                                             std::vector<glm::vec2> tex_UVs,
                                             std::vector<glm::vec3> normals)
{
    std::vector<Vertex> vertices;
    for (size_t i = 0; i < pos.size(); i++)
        vertices.push_back(
            Vertex{pos[i], glm::vec3(1.0f, 1.0f, 1.0f), tex_UVs[i], normals[i]}
        );

    return vertices;
}

std::vector<glm::vec2> Model::group_floats_vec2(std::vector<float> floats)
{
    std::vector<glm::vec2> vec2s;
    for (size_t i = 0; i < floats.size();)
        vec2s.push_back(glm::vec2(floats[i++], floats[i++]));

    return vec2s;
}

std::vector<glm::vec3> Model::group_floats_vec3(std::vector<float> floats)
{
    std::vector<glm::vec3> vec3s;
    for (size_t i = 0; i < floats.size();)
        vec3s.push_back(glm::vec3(floats[i++], floats[i++], floats[i++]));

    return vec3s;
}

std::vector<glm::vec4> Model::group_floats_vec4(std::vector<float> floats)
{
    std::vector<glm::vec4> vec4s;
        for (size_t i = 0; i < floats.size();)
        vec4s.push_back(glm::vec4(floats[i++], floats[i++], floats[i++], floats[i++]));

    return vec4s;
}
