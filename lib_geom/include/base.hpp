//
// Created by mazrog on 16/11/17.
//

#ifndef ENGINE_BASE_HPP
#define ENGINE_BASE_HPP

#include <iostream>
#include <glm/glm.hpp>

using mat4 = glm::mat4;
using vec3 = glm::vec3;

void translate(mat4 & transform, vec3 && delta);

void scale(mat4 & transform, vec3 && factor);

void rotate(mat4 & transform, float angle, vec3 && axis);

template < class T >
void debug(T const& m){
    for(int i = 0; i < m.length(); ++i){
        std::cout << m[i].x << " # " << m[i].y << " # " << m[i].z << " # " << m[i].w << " # " << std::endl;
    }
    std::cout << std::endl;
}

#endif //ENGINE_BASE_HPP
