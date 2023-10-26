/**
* \file scene.hpp
* \brief provides class Scene
* \author João Vitor Espig (JotaEspig)
* \date October 25, 2023
* \version October 25, 2023
**/
#pragma once

#include <vector>

#include <axolote/drawable.hpp>
#include <axolote/camera.hpp>

namespace axolote
{

/**
* \brief Describes a scene
* \author João Vitor Espig (JotaEspig)
* \date October 25, 2023
* \version October 25, 2023
**/
class Scene
{
public:
    /** Camera in the scene **/
    Camera camera;
    /** vector of drawable objects **/
    std::vector<Drawable> drawable_objects;

    Scene();
    ~Scene();

    /** updates the camera and objects position **/
    void update();
    /** draws in the window **/
    void render();

};

} // namespace axolote
