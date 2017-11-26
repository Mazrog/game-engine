//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_SG_HPP
#define ENGINE_SG_HPP

#include <vector>
#include <map>
#include <memory>
#include <glm/glm.hpp>

#include "utils.hpp"

enum class SG_NODE_TYPE : unsigned {
    SG_STATIC,
    SG_DYNAMIC,
    SG_CAMERA,
    SG_LIGHT,
    SG_FORCE
};


struct RenderingData {
    std::unique_ptr<vecord> vertices;
    std::unique_ptr<vecuvs> uvs;
    std::unique_ptr<vecord> normals;
    std::unique_ptr<vecui>  links;

    RenderingData();
};

struct DynamicData{
    std::unique_ptr<glm::mat4>  tranform;

    DynamicData();
};

#endif //ENGINE_SG_HPP
