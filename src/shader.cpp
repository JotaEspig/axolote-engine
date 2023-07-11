#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <axolote/shader.hpp>

using namespace axolote;

static std::string get_file_content(const char *filename)
{
    std::ifstream in(filename, std::ios::binary);
    if (!in)
        throw (errno);

    std::string content;
    in.seekg(0, std::ios::end);
    content.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&content[0], content.size());
    in.close();
    return content;
}

static GLint check_shader_compilation(GLuint shader_id, char *log, size_t size)
{
    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
        glGetShaderInfoLog(shader_id, size, NULL, log);

    return success;
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

void Shader::set_uniform_matrix4(const char *uniform_name, glm::mat4 matrix)
{
    GLuint uniform_location = glGetUniformLocation(id, uniform_name);
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::activate()
{
    glUseProgram(id);
}

void Shader::destroy()
{
    glDeleteProgram(id);
}
