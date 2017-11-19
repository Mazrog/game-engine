//
// Created by mazrog on 15/11/17.
//


#include "rendering/uniform.hpp"

Uniform::Uniform(GLuint progid, const char *name) : progid(progid), location(), name(name) {
    location = glGetUniformLocation(progid, name); get_error();
}