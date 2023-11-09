/**
* \file scene.hpp
* \brief provides class Scene
* \author João Vitor Espig (JotaEspig)
* \date October 25, 2023
* \version November 08, 2023
**/
#pragma once

#include <vector>

#include <axolote/drawable.hpp>
#include <axolote/entity.hpp>
#include <axolote/object3d.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/camera.hpp>

namespace axolote
{

/**
* \brief Describes a scene
* \author João Vitor Espig (JotaEspig)
* \date October 25, 2023
* \version November 08, 2023
**/
class Scene
{
public:
    /** vector of Entity objects **/
    std::vector<Entity*> entity_objects;
    /** vector of Entity objects **/
    std::vector<Object3D> object3d_objects;
    /** Camera in the scene **/
    Camera camera;

    Scene();
    ~Scene();

    /**
     * \brief add an Entity to the scene
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
    **/
    void add_drawable(Entity *e);
    /**
     * \brief add an Object3D to the scene
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
    **/
    void add_drawable(const Object3D &m);
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
     * \version November 08, 2023
    **/
    void update(double time);
    /**
     * \brief draw the drawables
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
    **/
    void render();

private:
    /** vector of shaders from drawable objects **/
    std::vector<Shader> shaders;
};

} // namespace axolote
