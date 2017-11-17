//
// Created by mazrog on 13/11/17.
//

#include <iostream>

#include "rendering/camera.hpp"

Camera::Camera() {
    draw_order = -1;
    dynamicData.tranform = std::make_unique<glm::mat4>();
}

void Camera::render() {

}