//
// Created by mazrog on 18/12/17.
//

#ifndef ENGINE_MODEL_HPP
#define ENGINE_MODEL_HPP

#include "scenegraph/scenegraph.hpp"

struct Material {
    float ka;
    float kd;
    float ks;
};


struct Model {
    Model();
    Model(const char * file);
    void clear();


    vecord  vertices;
    vecuvs  uvs;
    vecord  normals;
    vecui   links;

    Material material;
};


#endif //ENGINE_MODEL_HPP
