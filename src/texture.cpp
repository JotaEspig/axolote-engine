#include <glad/glad.h>
#include <stb/stb_image.h>

#include <axolote/texture.hpp>
#include <axolote/shader.hpp>

using namespace axolote;

Texture::Texture()
{
    loaded = false;
}

Texture::Texture(const char *texture_file, GLenum _type, GLuint _unit, GLenum format,
                 GLenum pixel_type)
{
    loaded = false;
    type = _type;
    unit = _unit;

    stbi_set_flip_vertically_on_load(true);
    int width_img, height_img, num_channels_img;
    unsigned char *data = stbi_load(texture_file, &width_img, &height_img,
                                    &num_channels_img, 0);
    if (!data)
        return;

    glGenTextures(1, &id);
    activate();
    bind();

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(type, 0, format, width_img, height_img, 0, format, pixel_type, data);

    glGenerateMipmap(type);

    stbi_image_free(data);
    unbind();
    loaded = true;
}

void Texture::activate()
{
    glActiveTexture(GL_TEXTURE0 + unit);
}

void Texture::bind()
{
    glBindTexture(type, id);
}

void Texture::unbind()
{
    glBindTexture(type, 0);
}

void Texture::destroy()
{
    glDeleteTextures(1, &id);
}
