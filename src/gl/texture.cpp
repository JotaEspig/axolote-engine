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
    GLuint id = _id;
    glDeleteTextures(1, &_id);
    debug("Texture destroyed: %u", id);
}

Texture::Texture() {
    glGenTextures(1, &_id);
    debug("Texture created: %u", _id);
}

Texture::Texture(
    std::string texture_filename, std::string tex_type, GLuint unit
) :
  Texture{} {
    _type = tex_type;
    _unit = unit;
    stbi_set_flip_vertically_on_load(true);
    int width_img, height_img, num_channels_img;
    unsigned char *data = stbi_load(
        texture_filename.c_str(), &width_img, &height_img, &num_channels_img, 0
    );
    if (!data)
    {
        debug("Failed to load texture: %s", texture_filename.c_str());
        return;
    }

    activate();
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (num_channels_img == 4)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width_img, height_img, 0, GL_RGBA,
            GL_UNSIGNED_BYTE, data
        );
    else if (num_channels_img == 3)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width_img, height_img, 0, GL_RGB,
            GL_UNSIGNED_BYTE, data
        );
    else if (num_channels_img == 1)
        glTexImage2D(
            GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, width_img, height_img, 0, GL_RED,
            GL_UNSIGNED_BYTE, data
        );
    else
        throw std::invalid_argument("Texture type recognition failed");

    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
    _loaded = true;
    debug("Texture loaded: %s", texture_filename.c_str());
}

void Texture::Deleter::operator()(Texture *texture) {
    texture->destroy();
    delete texture;
}

} // namespace gl

} // namespace axolote
