//
// Created by mazrog on 03/12/17.
//

#include "rendering/structs/vao.hpp"


Vao::Vao() {
    glGenVertexArrays(1, &id); get_error("VAO creation");
}

Vao::~Vao() { clean(); }

Vao::Vao(Vao && vao) : id(vao.id), vbos(std::move(vao.vbos)) { vao.id = 0; }

Vao& Vao::operator=(Vao && vao) {
    id = vao.id;
    vbos = vao.vbos;
    vao.id = 0;
    vao.vbos.clear();

    return *this;
}

void Vao::bind() {
    glBindVertexArray(id);  get_error("VAO binding");
}

void Vao::clean() {
    if(id) {
        for (auto &vbo: vbos) { vbo.clean(); }

        glBindVertexArray(0);
        get_error("VAO unbinding");
        glDeleteVertexArrays(1, &id);
        get_error("VAO deletion");
    }
}