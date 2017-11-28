//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include <iostream>

#include "vector_utils.hpp"
#include "scenegraph/scenegraph.hpp"

void get_error(const char * t = "");


namespace Loader {

    struct Vertex {
        int vertex_index;
        int texture_index;
        int normal_index;
        glm::vec3  position;

        bool isSet() { return texture_index > 0 && normal_index > 0; }
        bool hasSameIndices(int text, int norm) { return texture_index == text && normal_index == norm; }

        Vertex(int index, glm::vec3 const& vec) : vertex_index(index), texture_index(-1), normal_index(-1), position(vec) {}
        Vertex(int v = -1, int vt = -1, int vn = -1) : vertex_index(v), texture_index(vt), normal_index(vn) {}
    };

    /* Operator == overloading */
    inline bool operator==(Vertex & v1, Vertex & v2) {
        return v1.texture_index == v2.texture_index && v1.normal_index == v2.normal_index;
    }

    /* Operator != */
    inline bool operator!=(Vertex & v1, Vertex & v2) {
        return v1.texture_index != v2.texture_index || v1.normal_index != v2.normal_index;
    }

    void load_obj(const char * file, Model & model);
}

#endif //ENGINE_UTILS_HPP
