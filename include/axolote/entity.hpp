#pragma once

#include <glm/glm.hpp>

#include <axolote/model.hpp>
#include <axolote/mesh.hpp>
#include <axolote/shader.hpp>

namespace axolote
{ 
    enum class EntityType
    {
        MODEL,
        MESH
    };

    class Entity
    {
        EntityType type;
        Model model;
        Mesh mesh;
        glm::mat4 matrix = glm::mat4(1.0f);

    public:
        Entity();
        void set_matrix(glm::mat4 mat = glm::mat4(1.0f));
        void draw(Shader shader);
        void set_model(Model m);
        void set_mesh(Mesh m);
    };
}
