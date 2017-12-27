//
// Created by mazrog on 10/11/17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "scenegraph/scenegraph.hpp"


DynamicData::DynamicData() {
    transform = glm::mat4();
    position = glm::vec3(0.0);
    rotation = glm::vec3(0.0);
    scale    = glm::vec3(1);
}

void DynamicData::update() {
    transform = glm::translate(glm::mat4(1.f), position);
    transform = glm::scale(transform, scale);
}