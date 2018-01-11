//
// Created by mazrog on 11/01/18.
//

#include "rendering/entity.hpp"

Entity::Entity(const char * model_name, glm::vec3 position,
               glm::vec3 rotation, glm::vec3 scale) : SGL_Node(model_name) {
    dynamicData = DynamicData(position, rotation, scale);
    dynamicData.update();

    renderer.setData(this);
}