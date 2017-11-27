//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_SG_HPP
#define ENGINE_SG_HPP

#include <vector>
#include <map>
#include <memory>
#include <glm/glm.hpp>

using vecord = std::vector<glm::vec3>;
using vecuvs = std::vector<glm::vec2>;
using vecui  = std::vector<unsigned>;

enum class SG_NODE_TYPE : unsigned {
    SG_STATIC,
    SG_DYNAMIC,
    SG_CAMERA,
    SG_LIGHT,
    SG_FORCE
};

struct Material {
    float ka;
    float kd;
    float ks;
};

struct Model {
    vecord  vertices;
    vecuvs  uvs;
    vecord  normals;
    vecui   links;

    Material material;

    Model();
};

struct DynamicData{
    glm::mat4  tranform;

    DynamicData();
};

#endif //ENGINE_SG_HPP
