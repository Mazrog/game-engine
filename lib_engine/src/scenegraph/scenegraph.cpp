//
// Created by mazrog on 10/11/17.
//

#include "scenegraph/scenegraph.hpp"

RenderingData::RenderingData() {
    vertices  = std::make_unique<vecord>();
    uvs       = std::make_unique<vecuvs>();
    normals   = std::make_unique<vecord>();
    links     = std::make_unique<vecui>();
}

DynamicData::DynamicData() {
    tranform = std::make_unique<glm::mat4>();
}