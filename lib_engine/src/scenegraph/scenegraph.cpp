//
// Created by mazrog on 10/11/17.
//

#include "scenegraph/scenegraph.hpp"

Model::Model() {
    vertices  = vecord();
    uvs       = vecuvs();
    normals   = vecord();
    links     = vecui();
}

DynamicData::DynamicData() {
    tranform = glm::mat4();
}