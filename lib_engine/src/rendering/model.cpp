//
// Created by mazrog on 18/12/17.
//

#include <scenegraph/scenegraph.hpp>
#include <utils.hpp>

Model::Model() {
    vertices  = vecord();
    uvs       = vecuvs();
    normals   = vecord();
    links     = vecui();
}

Model::Model(const char * file) : Model() {
    Loader::load_obj_element(file, *this);
}

void Model::clear() {
    vertices.clear();
    uvs.clear();
    normals.clear();
    links.clear();
}