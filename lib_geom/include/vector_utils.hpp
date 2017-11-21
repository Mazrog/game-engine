//
// Created by mazrog on 19/11/17.
//

#ifndef ENGINE_VECTOR_UTILS_HPP
#define ENGINE_VECTOR_UTILS_HPP

#include <cmath>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

template < typename T >
using cref = T const&;

using crvec3  = cref<glm::vec3>;
using crfloat = cref<float>;

void angle_between(crvec3 u, crvec3 v, float & pitch, float & yaw);

void apply_rot(glm::vec3 & point, crfloat angle, crvec3 axis);

glm::vec3 pdt_vec(crvec3 u, crvec3 v);


template < class T >
float pdt_scalar(cref<T> u, cref<T> v) {
    float res = 0.f;
    for(unsigned i = 0; i < u.length(); ++i){ res += u[i] * v[i]; }
    return res;
}

template < class T >
float norm_2(cref<T> u) {
    float res = 0.f;
    for(int i = 0; i < u.length(); ++i){ res += powf(u[i], 2); }
    return sqrtf(res);
}

#endif //ENGINE_VECTOR_UTILS_HPP
