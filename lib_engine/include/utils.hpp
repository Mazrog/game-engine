//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_UTILS_HPP
#define ENGINE_UTILS_HPP

#include <glm/vec3.hpp>

template < typename T >
using cref = T const&;

using crvec3 = cref<glm::vec3>;

void get_error(const char * t = "");


#endif //ENGINE_UTILS_HPP
