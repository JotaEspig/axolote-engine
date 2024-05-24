/**
 * \file scene.hpp
 * \brief provides class Scene
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version May 23, 2024
 **/
#pragma once

#include <memory>
#include <vector>

#include <axolote/camera.hpp>
#include <axolote/drawable.hpp>
#include <axolote/entity.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/object3d.hpp>

namespace axolote {

/**
 * \brief Describes a scene
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version May 24, 2024
 **/
class Scene {
public:
    /** vector of drawables objects **/
    std::vector<std::shared_ptr<Drawable>> drawable_objects;
    /** Camera in the scene **/
    Camera camera;

    /**
     * \brief Constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
     **/
    Scene();
    /**
     * \brief Destructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
     **/
    ~Scene();

    /**
     * \brief add a Drawable object to the scene
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version May 24, 2024
     **/
    void add_drawable(std::shared_ptr<Drawable> d);
    /**
     * \brief updates the camera in the shaders
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
     **/
    void update_camera(float aspect_ratio);
    /**
     * \brief updates the drawables
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version May 24, 2024
     **/
    void update(double time);
    /**
     * \brief draw the drawables
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version May 24, 2024
     **/
    void render();

private:
    /** vector of shaders from drawable objects **/
    std::vector<gl::Shader> shaders;
};

} // namespace axolote
