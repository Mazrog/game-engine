//
// Created by mazrog on 10/11/17.
//

#include "scenegraph/scenegraph.hpp"

RenderingData::RenderingData() {
    vertices    = std::vector<glm::vec3>();
    uvs         = std::vector<glm::vec3>();
    normals     = std::vector<glm::vec3>();
    links       = std::vector<unsigned >();
}