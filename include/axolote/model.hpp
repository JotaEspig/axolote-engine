#pragma once

#include <vector>

#include <GL/gl.h>
#include <glm/glm.hpp>
#include <json/json.hpp>

#include <axolote/shader.hpp>
#include <axolote/mesh.hpp>
#include <axolote/texture.hpp>
#include <axolote/structs.hpp>

using json = nlohmann::json;

namespace axolote
{
    class Model
    {
    public:
        Model(const char *_filename);

        void draw(Shader &shader);

    private:
        const char *filename;
        std::vector<unsigned char> data;
        json json_obj;
        std::vector<Mesh> meshes;
        std::vector<glm::vec3> translations_meshes;
        std::vector<glm::quat> rotations_meshes;
        std::vector<glm::vec3> scales_meshes;
        std::vector<glm::mat4> matrices_meshes;
        std::vector<Texture> loaded_tex;
        std::vector<std::string> loaded_tex_name;

        void load_mesh(unsigned int ind_mesh);
        void traverse_node(unsigned int next_node, glm::mat4 matrix = glm::mat4(1.0f));
        std::vector<unsigned char> get_data();
        std::vector<float> get_floats(json accessor);
        std::vector<GLuint> get_indices(json accessor);
        std::vector<Texture> get_textures();

        std::vector<Vertex> assemble_vertices(std::vector<glm::vec3> pos,
                                              std::vector<glm::vec2> tex_UVs,
                                              std::vector<glm::vec3> normals);

        std::vector<glm::vec2> group_floats_vec2(std::vector<float> floats);
        std::vector<glm::vec3> group_floats_vec3(std::vector<float> floats);
        std::vector<glm::vec4> group_floats_vec4(std::vector<float> floats);
    };
}
