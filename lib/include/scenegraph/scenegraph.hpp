//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_SG_HPP
#define ENGINE_SG_HPP

#include <vector>
#include <map>
#include <glm/glm.hpp>

enum class SG_NODE_TYPE : unsigned {
    SG_STATIC,
    SG_DYNAMIC,
    SG_CAMERA,
    SG_FORCE
};


struct RenderingData {
    std::vector<glm::vec3>  vertices;
    std::vector<glm::vec3>  uvs;
    std::vector<glm::vec3>  normals;
    std::vector<unsigned >  links;

    RenderingData();
};

#endif //ENGINE_SG_HPP
