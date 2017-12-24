//
// Created by mazrog on 18/12/17.
//

#include "scenegraph/scenegraph.hpp"
#include "utils.hpp"
#include "rendering/model.hpp"

Model::Model() {
    vertices  = vecf();
    uvs       = vec2f();
    normals   = vecf();
    links     = vecui();
    mtlLib    = MtlLib();
}

Model::Model(const char * file) : Model() {
    Loader::load_obj_array(file, *this);
}

Model::~Model() {
    for( auto & pair : mtlLib ) {
        delete pair.second;
    }
}

void Model::clear() {
    vertices.clear();
    uvs.clear();
    normals.clear();
    links.clear();
}