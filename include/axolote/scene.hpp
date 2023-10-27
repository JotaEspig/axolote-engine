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
* \version October 25, 2023
**/
class Scene
{
public:
    /** Camera in the scene **/
    Camera camera;

    Scene();
    ~Scene();

    void add_drawable(Entity *e);
    void add_drawable(const Object3D &m);
    void update_camera(float aspect_ratio);
    /** updates the objects position **/
    void update(double time);
    /** draws in the window **/
    void render();

private:
    /** vector of Entity objects **/
    std::vector<Entity*> entity_objects;
    /** vector of Entity objects **/
    std::vector<Object3D> object3d_objects;
    /** vector of shaders from drawable objects **/
    std::vector<Shader> shaders;
};

} // namespace axolote
