//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_SG_HPP
#define ENGINE_SG_HPP

#include <vector>
#include <map>
#include <memory>
#include <glm/glm.hpp>

using vecf = std::vector<glm::vec3>;
using vec2f = std::vector<glm::vec2>;
using vecui  = std::vector<unsigned>;

enum class SG_NODE_TYPE : unsigned {
    SG_STATIC,
    SG_DYNAMIC,
    SG_CAMERA,
    SG_LIGHT,
    SG_FORCE
};

struct DynamicData{
    glm::mat4   transform;
    glm::vec3   position;
    glm::vec3   rotation;
    glm::vec3   scale;

    DynamicData(glm::vec3 position = glm::vec3(0.f),
                glm::vec3 rotation = glm::vec3(0.f),
                glm::vec3 scale    = glm::vec3(1.f));

    void update();
};

#endif //ENGINE_SG_HPP
