/**
 * @file cubemap.hpp
 * @brief Cubemap class
 **/
#pragma once

#include <memory>
#include <string>

#include "axolote/glad/glad.h"

#include "axolote/gl/opengl_object.hpp"

namespace axolote {

namespace gl {

class Cubemap : public OpenGLObject {
public:
    /**
     * @brief Creates a cubemap
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @return shared pointer to cubemap
     **/
    template <typename... Args>
    static std::shared_ptr<Cubemap> create(Args &&...args);

    /**
     * @brief id getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    GLuint id() const override;
    /**
     * @brief loaded getter
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    bool is_loaded() const;
    /**
     * @brief activates texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void activate();
    /**
     * @brief binds texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void bind();
    /**
     * @brief unbinds texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void unbind();
    /**
     * @brief destroys texture
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    void destroy() override;

private:
    struct Deleter {
        void operator()(Cubemap *cubemap);
    };

    /** OpenGL texture id **/
    GLuint _id;
    /** texture is loaded **/
    bool _loaded = false;

    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     **/
    Cubemap();
    /**
     * @brief Constructor
     * @author João Vitor Espig (jotaespig@gmail.com)
     * @param texture_faces_filenames name of texture files for the faces
     **/
    Cubemap(std::string texture_faces_filenames[6]);
};

template <typename... Args>
std::shared_ptr<Cubemap> Cubemap::create(Args &&...args) {
    return std::shared_ptr<Cubemap>{
        new Cubemap{std::forward<Args>(args)...}, Deleter{}
    };
}

} // namespace gl
} // namespace axolote
