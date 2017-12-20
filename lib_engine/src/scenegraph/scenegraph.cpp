//
// Created by mazrog on 10/11/17.
//

#include "scenegraph/scenegraph.hpp"


DynamicData::DynamicData() {
    transform = glm::mat4();
    position = glm::vec3(0.0);
    rotation = glm::vec3(0.0);
    scale    = glm::vec3(1);
}

void DynamicData::update() {
    transform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            position.x, position.y + 20, position.z, 1.f
    );
}