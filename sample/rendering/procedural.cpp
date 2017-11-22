//
// Created by mazrog on 21/11/17.
//

#include <iostream>
#include "utils.hpp"
#include "procedural.hpp"

ShaderProgram Procedural::prog;

void Procedural::init() {
    if(!Procedural::prog.getProgId()) {
        Procedural::prog = ShaderProgram("sample/shaders/proc_vert.glsl", "sample/shaders/proc_frag.glsl");
    }
}

Procedural::Procedural() : vao(), vbos(), transform() {}

Procedural::Procedural(SGL_Node *node) :
        transform(prog.getProgId(), "transform") {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(2, vbos);      get_error("gen buffer");
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer vertices");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error("buffer data vertices");

    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) 0); get_error("set pointer 0");

    glEnableVertexAttribArray(1); get_error("enable pointer 1");
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void *) (3*sizeof(GLfloat))); get_error("set pointer 1");
}

void Procedural::operator()(DynamicData const &dd) {
    operator()(dd, GL_TRIANGLES);
}

void Procedural::operator()(DynamicData const &dd, GLenum primitive) {
    glBindVertexArray(vao); get_error("bind vao render");
    transform.send(*dd.tranform);

    glDrawArrays(primitive, 0, 6); get_error("rendering_procedural");
}