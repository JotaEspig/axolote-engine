#include <stdexcept>
#include <string>

#include <stb/stb_image.h>

#include "axolote/glad/glad.h"

#include "axolote/gl/texture.hpp"
#include "axolote/utils.hpp"

namespace axolote {

namespace gl {

GLuint Texture::id() const {
    return _id;
}

std::string Texture::type() const {
    return _type;
}

GLuint Texture::unit() const {
    return _unit;
}

bool Texture::is_loaded() const {
    return _loaded;
}

void Texture::activate() {
    glActiveTexture(GL_TEXTURE0 + _unit);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, _id);
}

void Texture::unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy() {
    debug("Texture destroyed: %u\n", _id);
    glDeleteTextures(1, &_id);
}

Texture::Texture() :
  _loaded{false} {
}

Texture::Texture(
    const char *texture_filename, std::string tex_type, GLuint unit
) :
  _type{tex_type},
  _unit{unit},
  _loaded{false} {
    stbi_set_flip_vertically_on_load(true);
    int width_img, height_img, num_channels_img;
    unsigned char *data = stbi_load(
        texture_filename, &width_img, &height_img, &num_channels_img, 0
    );
    if (!data)
        return;

    glGenTextures(1, &_id);
    activate();
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (num_channels_img == 4)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, data
        );
    else if (num_channels_img == 3)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data
        );
    else if (num_channels_img == 1)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0, GL_RED,
            GL_UNSIGNED_BYTE, data
        );
    else
        throw std::invalid_argument("Texture type recognition failed");

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    _loaded = true;

    debug("Texture created: %u\n", _id);
}

void Texture::Deleter::operator()(Texture *texture) {
    texture->destroy();
    delete texture;
}

} // namespace gl

} // namespace axolote
