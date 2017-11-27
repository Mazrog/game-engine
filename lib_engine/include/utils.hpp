//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include "vector_utils.hpp"
#include "scenegraph/scenegraph.hpp"

void get_error(const char * t = "");


namespace Loader {
    void load_obj(const char * file, Model & model);
}

#endif //ENGINE_UTILS_HPP
