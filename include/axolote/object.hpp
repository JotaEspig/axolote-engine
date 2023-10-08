/**
* \file object.hpp
* \brief Object abstract class
* \author João Vitor Espig (JotaEspig)
* \date October 06, 2023
* \version October 06, 2023
**/
#pragma once

#include <glm/glm.hpp>

#include <axolote/shader.hpp>

namespace axolote
{

/**
* \brief defines an abstract Object
* \author João Vitor Espig (JotaEspig)
* \date October 06, 2023
* \version October 06, 2023
**/
class Object
{
public:
    /**
    * \brief draws
    * \author João Vitor Espig (JotaEspig)
    * \date October 06, 2023
    * \version October 06, 2023
    * \param shader - Shader object
    **/
    virtual void draw(Shader &shader) = 0;

protected:
    /** model transformation matrix **/
    glm::mat4 pos = glm::mat4(1.0f);
};

} // namespace axolote
