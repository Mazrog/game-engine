//
// Created by mazrog on 21/11/17.
//

#include <iostream>
#include "utils.hpp"
#include "procedural.hpp"

ShaderProgram Procedural::prog;

void Procedural::init() {
    if(!Procedural::prog.getProgId()) {
        Procedural::prog = ShaderProgram();
        Procedural::prog.makeShader("sample/shaders/proc_vert.glsl", GL_VERTEX_SHADER);
        Procedural::prog.makeShader("sample/shaders/proc_frag.glsl", GL_FRAGMENT_SHADER);
        Procedural::prog.linkProgram();
    }
}

Procedural::Procedural() : vao(), vbos(), transform() {}

Procedural::Procedural(SGL_Node *node) :
        transform(prog.getProgId(), "transform"), y_max(prog.getProgId(), "ymax") {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(2, vbos);      get_error("gen buffer");
//    glBindBuffer(GL_SHADER_STORAGE_BUFFER, vbos[0]); get_error("bind storage buffer");
//    glBufferData(GL_SHADER_STORAGE_BUFFER, 100 * sizeof(glm::vec3), nullptr, GL_STATIC_DRAW); get_error("buffer storage data");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer vertices");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error("buffer data vertices");

    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 0");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]); get_error("bind buffer element");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * rd.links->size(), rd.links->data(), GL_STATIC_DRAW); get_error("buffer element data");

    y_max.send(2.f);
}

void Procedural::operator()(DynamicData const &dd) {
    operator()(dd, GL_TRIANGLES);
}

void Procedural::operator()(DynamicData const &dd, GLenum primitive) {
    glBindVertexArray(vao); get_error("bind vao render");
    transform.send(*dd.tranform);

    glDrawElements(primitive, 600, GL_UNSIGNED_INT, (void *) 0); get_error("rendering_procedural");
}