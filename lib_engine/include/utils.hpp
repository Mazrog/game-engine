//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include "vector_utils.hpp"

using vecord = std::vector<glm::vec3>;
using vecuvs = std::vector<glm::vec2>;
using vecui  = std::vector<unsigned>;

void get_error(const char * t = "");


namespace Loader {
    void load_obj(const char * file, vecord & vertices, vecuvs & uvs, vecord & normals, vecui & links);
}

#endif //ENGINE_UTILS_HPP
