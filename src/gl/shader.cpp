#include <cerrno>
#include <iostream>
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/gl/shader.hpp>
#include <axolote/utils.hpp>

static GLint check_shader_compilation(GLuint shader_id, char *log, size_t size)
{
    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
        glGetShaderInfoLog(shader_id, size, NULL, log);

    return success;
}

namespace axolote
{

namespace gl
{

Shader::Shader()
{
}

Shader::Shader(const Shader &shader) :
    id{shader.id}
{
}

Shader::Shader(Shader &&shader) :
    id{std::move(shader.id)}
{
}

Shader::Shader(const char *vertex_file, const char *fragment_file)
{
    std::string vertex_code = get_file_content(vertex_file);
    std::string fragment_code = get_file_content(fragment_file);
    const char *vertex_src = vertex_code.c_str();
    const char *fragment_src = fragment_code.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_src, NULL);

    glCompileShader(vertex_shader);
    GLchar info_log[512];
    if (!check_shader_compilation(vertex_shader, info_log, 512))
        std::cerr << "Error when compiling shader: " << info_log << std::endl;

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_src, NULL);

    glCompileShader(fragment_shader);
    if (!check_shader_compilation(fragment_shader, info_log, 512))
        std::cerr << "Error when compiling shader: " << info_log << std::endl;

    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::set_uniform_int(const char *uniform_name, int value)
{
    activate();
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniform1i(uniform_location, value);
}

void Shader::set_uniform_matrix4(
    const char *uniform_name, const glm::mat4 &matrix
)
{
    activate();
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_uniform_float(const char *uniform_name, float x)
{
    activate();
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniform1f(uniform_location, x);
}

void Shader::set_uniform_float3(
    const char *uniform_name, float x, float y, float z
)
{
    activate();
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniform3f(uniform_location, x, y, z);
}

void Shader::set_uniform_float4(
    const char *uniform_name, float x, float y, float z, float w
)
{
    activate();
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniform4f(uniform_location, x, y, z, w);
}

void Shader::activate()
{
    glUseProgram(id);
}

void Shader::destroy()
{
    glDeleteProgram(id);
}

void Shader::operator=(const Shader &shader)
{
    id = shader.id;
}

void Shader::operator=(Shader &&shader)
{
    id = std::move(shader.id);
}

} // namespace gl

} // namespace axolote