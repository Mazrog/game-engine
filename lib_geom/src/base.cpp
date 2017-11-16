//
// Created by mazrog on 16/11/17.
//

#include "base.hpp"

void translate(mat4 & transform, vec3 && delta) {
    transform[3] += glm::vec4(delta, 0.f);
}

void scale(mat4 & transform, vec3 && factor){
    transform[0].x *= factor.x;
    transform[1].y *= factor.y;
    transform[2].z *= factor.z;
}