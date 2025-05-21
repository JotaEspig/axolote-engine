#include <iostream>
#include <string>
#include <stdexcept>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "axolote/glad/glad.h"

#include "axolote/gl/shader.hpp"
#include "axolote/utils.hpp"

static GLint
check_shader_compilation(GLuint shader_id, char *log, size_t size) {
    GLint success;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success)
        glGetShaderInfoLog(shader_id, size, NULL, log);

    return success;
}

namespace axolote {

namespace gl {

std::shared_ptr<Shader> Shader::create_from_source_code(
    const char *vertex_source_code, const char *fragment_source_code
) {
    std::shared_ptr<Shader> shader = Shader::create();
    shader->compile(vertex_source_code, fragment_source_code);
    return shader;
}

GLuint Shader::id() const {
    return _id;
}

void Shader::set_uniform_int(const char *uniform_name, int value) {
    use();
    GLuint uniform_location = glGetUniformLocation(_id, uniform_name);
    glUniform1i(uniform_location, value);
}

void Shader::set_uniform_matrix4(
    const char *uniform_name, const glm::mat4 &matrix
) {
    use();
    GLuint uniform_location = glGetUniformLocation(_id, uniform_name);
    glUniformMatrix4fv(uniform_location, 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::set_uniform_float(const char *uniform_name, float x) {
    use();
    GLuint uniform_location = glGetUniformLocation(_id, uniform_name);
    glUniform1f(uniform_location, x);
}

void Shader::set_uniform_float3(
    const char *uniform_name, float x, float y, float z
) {
    use();
    GLuint uniform_location = glGetUniformLocation(_id, uniform_name);
    glUniform3f(uniform_location, x, y, z);
}

void Shader::set_uniform_float4(
    const char *uniform_name, float x, float y, float z, float w
) {
    use();
    GLuint uniform_location = glGetUniformLocation(_id, uniform_name);
    glUniform4f(uniform_location, x, y, z, w);
}

void Shader::use() {
    glUseProgram(_id);
}

void Shader::compile(
    const std::string &vertex_code, const std::string &fragment_code
) {
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
    if (!check_shader_compilation(fragment_shader, info_log, 512)) {
        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);
        debug(DebugType::FATAL, "Shader compilation failed: %s", info_log);
        throw std::runtime_error("Shader compilation failed");
    }

    _id = glCreateProgram();
    glAttachShader(_id, vertex_shader);
    glAttachShader(_id, fragment_shader);

    glLinkProgram(_id);

    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);

    debug(DebugType::INFO, "Shader created: %u", _id);
}

void Shader::destroy() {
    glDeleteProgram(_id);
    debug(DebugType::INFO, "Shader destroyed: %u", _id);
}

Shader::Shader() {
}

Shader::Shader(std::string vertex_file, std::string fragment_file) {
    std::string vertex_code = get_file_content(vertex_file.c_str());
    std::string fragment_code = get_file_content(fragment_file.c_str());
    compile(vertex_code, fragment_code);
}

void Shader::Deleter::operator()(Shader *shader) {
    shader->destroy();
    delete shader;
}

} // namespace gl

} // namespace axolote
