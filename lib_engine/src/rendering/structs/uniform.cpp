//
// Created by mazrog on 15/11/17.
//


#include "rendering/structs/uniform.hpp"

Uniform::Uniform(GLuint progid, const char *name) : progid(progid), location(), name(name) {
    loadUniform(progid, name);
}

Uniform::~Uniform() {
    progid = 0;
    location = 0;
    name = nullptr;
}

Uniform::Uniform(Uniform && unif) :
        progid(unif.progid),
        location(unif.location),
        name(unif.name) {
    unif.progid = 0;
    unif.location = 0;
    unif.name = nullptr;
}

Uniform& Uniform::operator=(Uniform && unif) {
    progid = unif.progid;
    location = unif.location;
    name = unif.name;

    unif.progid = 0;
    unif.location = 0;
    unif.name = nullptr;

    return *this;
}

void Uniform::loadUniform(GLuint progID, const char * var_name) {
    if(progID) {
        progid = progID;
        name = var_name;
        ShaderProgram::useProgram(progid);
        location = glGetUniformLocation(progid, name); get_error("get unif location");
    }
}