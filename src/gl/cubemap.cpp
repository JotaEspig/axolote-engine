#include <stb/stb_image.h>

#include "axolote/glad/glad.h"

#include "axolote/gl/cubemap.hpp"
#include "axolote/utils.hpp"

namespace axolote {
namespace gl {

GLuint Cubemap::id() const {
    return _id;
}

bool Cubemap::is_loaded() const {
    return _loaded;
}

void Cubemap::activate() {
    glActiveTexture(GL_TEXTURE0);
}

void Cubemap::bind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}

void Cubemap::unbind() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

void Cubemap::destroy() {
    GLuint id = _id;
    glDeleteTextures(1, &_id);
    debug("Texture destroyed: %u", id);
}

Cubemap::Cubemap() {
    glGenTextures(1, &_id);
    debug("Cubemap created: %u", _id);
}

Cubemap::Cubemap(std::string texture_faces_filenames[6]) :
  Cubemap{} {
    bind();

    int width, height, num_channels;
    for (int i = 0; i < 6; i++) {
        unsigned char *data = stbi_load(
            texture_faces_filenames[i].c_str(), &width, &height, &num_channels,
            0
        );

        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0,
                GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else {
            debug(
                "Failed to load cubemap face texture at path: %s",
                texture_faces_filenames[i].c_str()
            );
            stbi_image_free(data);
            return;
        }

        debug(
            "Cubemap face texture loaded: %s",
            texture_faces_filenames[i].c_str()
        );
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    _loaded = true;
}

void Cubemap::Deleter::operator()(Cubemap *cubemap) {
    cubemap->destroy();
    delete cubemap;
}

} // namespace gl
} // namespace axolote
