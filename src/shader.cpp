#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cerrno>

#include <glad/glad.h>

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

Shader::Shader(const char *vertex_file, const char *fragment_file)
{
    std::string vertex_code = get_file_content(vertex_file);
    std::string fragment_code = get_file_content(fragment_file);
    const char *vertex_src = vertex_code.c_str();
    const char *fragment_src = fragment_code.c_str();

    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_src, NULL);

    glCompileShader(vertex_shader);
    GLint success;
    GLchar info_log[512];
    glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertex_shader, 512, NULL, info_log);
        std::cerr << "Vertex shader compilation failed: "
                  << info_log << std::endl;
        return;
    }

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_src, NULL);

    glCompileShader(fragment_shader);
    glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragment_shader, 512, NULL, info_log);
        std::cerr << "Fragment shader compilation failed: "
                  << info_log << std::endl;
        return;
    }

    id = glCreateProgram();
    glAttachShader(id, vertex_shader);
    glAttachShader(id, fragment_shader);

    glLinkProgram(id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::activate()
{
    glUseProgram(id);
}

void Shader::destroy()
{
    glDeleteProgram(id);
}
