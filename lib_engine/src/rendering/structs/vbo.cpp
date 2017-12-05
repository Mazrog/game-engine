//
// Created by mazrog on 03/12/17.
//

#include "rendering/structs/vbo.hpp"


Vbo::Vbo(GLenum type) : type(type) {
    glGenBuffers(1, &id); get_error("VBO creation");
}

Vbo::~Vbo() = default;

void Vbo::clean() {
    if(id) {
        glDeleteBuffers(1, &id);
        get_error("VBO deletion");
    }
}

void Vbo::bind() {
    glBindBuffer(type, id);  get_error("VBO binding");
}