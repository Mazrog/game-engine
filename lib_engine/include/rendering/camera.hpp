//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "scenegraph/sg_logic.hpp"


class Camera : public SGL_Node {
public:
    Camera();

    void render();

private:
    GLint  transform_loc;

    glm::vec3 pos;
    glm::vec3 aim;
    glm::vec3 normal;
};


#endif //ENGINE_CAMERA_HPP
