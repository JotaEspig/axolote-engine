#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/quaternion.hpp>

#include <axolote/gl/ebo.hpp>
#include <axolote/gl/vao.hpp>
#include <axolote/gl/vbo.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/mesh.hpp>
#include <axolote/structs.hpp>

namespace axolote
{

GMesh::GMesh()
{
}

GMesh::GMesh(const GMesh &gmesh) :
    Mesh{gmesh},
    vao{gmesh.vao},
    vbo{gmesh.vbo},
    ebo{gmesh.ebo},
    shader{gmesh.shader}
{
}

GMesh::GMesh(GMesh &&gmesh) :
    Mesh{std::move(gmesh)},
    vao{std::move(gmesh.vao)},
    vbo{std::move(gmesh.vbo)},
    ebo{std::move(gmesh.ebo)},
    shader{std::move(gmesh.shader)}
{
}

GMesh::GMesh(
    const std::vector<Vertex> &vertices, const std::vector<GLuint> &indices,
    const std::vector<gl::Texture> &textures
) :
    Mesh(vertices, indices, textures)
{
    vao.bind();
    vbo = gl::VBO(vertices);
    ebo = gl::EBO(indices);

    vao.link_attrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void *)0);
    vao.link_attrib(
        vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void *)(3 * sizeof(float))
    );
    vao.link_attrib(
        vbo, 2, 2, GL_FLOAT, sizeof(Vertex), (void *)(6 * sizeof(float))
    );
    vao.link_attrib(
        vbo, 3, 3, GL_FLOAT, sizeof(Vertex), (void *)(8 * sizeof(float))
    );
    vao.unbind();
    vbo.unbind();
    ebo.unbind();
}

void GMesh::bind_shader(const gl::Shader &shader)
{
    GMesh::shader = shader;
}

void GMesh::draw()
{
    draw(glm::mat4(1.0f));
}

void GMesh::draw(const glm::mat4 &mat)
{
    shader.activate();
    vao.bind();

    shader.set_uniform_int("is_specular_map_set", 0);
    if (textures.size() > 0)
        shader.set_uniform_int("is_tex_set", 1);
    else
        shader.set_uniform_int("is_tex_set", 0);

    unsigned int num_diffuse = 0;
    unsigned int num_specular = 0;
    // set default invalid values to textures to prevent a Mesh
    // to use a texture from another Mesh
    // TODO search if there's a better solution than this
    // i.e. set to 99 (a unused texture id)
    shader.set_uniform_int("diffuse0", 99);
    shader.set_uniform_int("specular0", 99);

    for (gl::Texture t : textures)
    {
        std::string num;
        std::string type = t.type;
        if (type == "diffuse")
            num = std::to_string(num_diffuse++);
        else if (type == "specular")
        {
            num = std::to_string(num_specular++);
            shader.set_uniform_int("is_specular_map_set", 1);
        }

        shader.set_uniform_int((type + num).c_str(), t.unit);
        t.activate();
        t.bind();
    }

    shader.set_uniform_matrix4("model", mat);

    vao.bind();
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    for (gl::Texture t : textures)
    {
        t.unbind();
    }
    vao.unbind();
}

void GMesh::destroy()
{
    vao.destroy();
    vbo.destroy();
    ebo.destroy();
}

void GMesh::operator=(const GMesh &gmesh)
{
    Mesh::operator=(gmesh);
    vao = gmesh.vao;
    vbo = gmesh.vbo;
    ebo = gmesh.ebo;
    shader = gmesh.shader;
}

void GMesh::operator=(GMesh &&gmesh)
{
    Mesh::operator=(std::move(gmesh));
    vao = std::move(gmesh.vao);
    vbo = std::move(gmesh.vbo);
    ebo = std::move(gmesh.ebo);
    shader = std::move(gmesh.shader);
}

} // namespace axolote
