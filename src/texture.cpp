#include <string>
#include <stdexcept>

#include <glad/glad.h>
#include <stb/stb_image.h>

#include <axolote/texture.hpp>
#include <axolote/shader.hpp>

namespace axolote
{

Texture::Texture() :
    loaded{false}
{
}

Texture::Texture(const char *texture_filename, std::string tex_type, GLuint _unit) :
    type{tex_type},
    unit{_unit},
    loaded{false}
{
    stbi_set_flip_vertically_on_load(true);
    int width_img, height_img, num_channels_img;
    unsigned char *data = stbi_load(texture_filename, &width_img, &height_img,
                                    &num_channels_img, 0);
    if (!data)
        return;

    glGenTextures(1, &id);
    activate();
    bind();

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    if (num_channels_img == 4)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0,
                     GL_RGBA, GL_UNSIGNED_BYTE, data);
    else if (num_channels_img == 3)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0,
                     GL_RGB, GL_UNSIGNED_BYTE, data);
    else if (num_channels_img == 1)
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_img, height_img, 0,
                     GL_RED, GL_UNSIGNED_BYTE, data);
    else
        throw std::invalid_argument("Texture type recognition failed");

    glGenerateMipmap(GL_TEXTURE_2D);

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
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::destroy()
{
    glDeleteTextures(1, &id);
}

} // namespace axolote
