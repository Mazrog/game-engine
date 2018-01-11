//
// Created by mazrog on 10/11/17.
//

#include <glm/gtc/matrix_transform.hpp>
#include "scenegraph/scenegraph.hpp"


DynamicData::DynamicData(glm::vec3 position,
                         glm::vec3 rotation,
                         glm::vec3 scale) : transform(), position(position), rotation(rotation), scale(scale) {
    update();
}

void DynamicData::update() {
    transform = glm::translate(glm::mat4(1.f), position);
    transform = glm::scale(transform, scale);
}