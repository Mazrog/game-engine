//
// Created by mazrog on 15/11/17.
//


#include "rendering/structs/uniform.hpp"

Uniform::Uniform(GLuint progid, const char *name) : progid(progid), location(), name(name) {
    if(progid) {
        ShaderProgram::useProgram(progid);
        location = glGetUniformLocation(progid, name); get_error("get unif location");
    }
}