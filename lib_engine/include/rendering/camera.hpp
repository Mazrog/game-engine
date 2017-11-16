//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/glm.hpp>

class Camera {
public:
    Camera();

private:
    glm::vec3 pos;
    glm::vec3 aim;
    glm::vec3 normal;
};


#endif //ENGINE_CAMERA_HPP
