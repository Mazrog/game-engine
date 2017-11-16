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
using vecui  = std::vector<unsigned>;

enum class SG_NODE_TYPE : unsigned {
    SG_STATIC,
    SG_DYNAMIC,
    SG_CAMERA,
    SG_FORCE
};


struct RenderingData {
    std::unique_ptr<vecord> vertices;
    std::unique_ptr<vecord> uvs;
    std::unique_ptr<vecord> normals;
    std::unique_ptr<vecui>  links;

    RenderingData() = default;
};

struct DynamicData{
    std::unique_ptr<glm::mat4>  tranform;

    DynamicData() = default;
};

#endif //ENGINE_SG_HPP
