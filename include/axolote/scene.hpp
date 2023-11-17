/**
 * \file scene.hpp
 * \brief provides class Scene
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version November 15, 2023
 **/
#pragma once

#include <memory>
#include <vector>

#include <axolote/camera.hpp>
#include <axolote/drawable.hpp>
#include <axolote/entity.hpp>
#include <axolote/gmesh.hpp>
#include <axolote/object3d.hpp>

namespace axolote
{

/**
 * \brief Describes a scene
 * \author João Vitor Espig (JotaEspig)
 * \date October 25, 2023
 * \version November 15, 2023
 **/
class Scene
{
public:
    /** vector of Entity objects **/
    std::vector<std::shared_ptr<Entity>> entity_objects;
    /** vector of Entity objects **/
    std::vector<std::shared_ptr<Object3D>> object3d_objects;
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
     * \brief Copy constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 09, 2023
     * \version November 09, 2023
     * \param scene - Scene object
     **/
    Scene(const Scene &scene);
    /**
     * \brief Move constructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 09, 2023
     * \version November 09, 2023
     * \param scene - Scene object
     **/
    Scene(Scene &&scene);
    /**
     * \brief Destructor
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 08, 2023
     **/
    ~Scene();

    /**
     * \brief add an Entity to the scene
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 15, 2023
     **/
    void add_drawable(std::shared_ptr<Entity> e);
    /**
     * \brief add an Object3D to the scene
     * \author João Vitor Espig (JotaEspig)
     * \date November 08, 2023
     * \version November 15, 2023
     **/
    void add_drawable(std::shared_ptr<Object3D> o);
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
    /**
     * \brief operator = overload (copy)
     * \author João Vitor Espig (JotaEspig)
     * \date November 09, 2023
     * \version November 09, 2023
     * \param scene - Scene object
     **/
    void operator=(const Scene &scene);
    /**
     * \brief operator = overload (move)
     * \author João Vitor Espig (JotaEspig)
     * \date November 09, 2023
     * \version November 09, 2023
     * \param scene - Scene object
     **/
    void operator=(Scene &&scene);

private:
    /** vector of shaders from drawable objects **/
    std::vector<Shader> shaders;
};

} // namespace axolote
