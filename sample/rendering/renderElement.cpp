//
// Created by mazrog on 14/11/17.
//

#include <iostream>
#include <rendering/program.hpp>

#include "display.hpp"
#include "renderElement.hpp"

ShaderProgram RenderElement::prog;

void RenderElement::init() {
    RenderElement::prog = ShaderProgram("sample/shaders/vert.glsl", "sample/shaders/frag.glsl");
}

RenderElement::RenderElement(SGL_Node * node) {
    RenderingData rd = node->get_data();

    glGenVertexArrays(1, &vao); get_error();
    glBindVertexArray(vao);     get_error();

    glGenBuffers(3, vbos);      get_error();

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices.size(), rd.vertices.data(), GL_STATIC_DRAW); get_error();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]); get_error();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * rd.links.size(), rd.links.data(), GL_STATIC_DRAW); get_error();


    glEnableVertexAttribArray(0); get_error();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error();
    glEnableVertexAttribArray(1); get_error();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error();
}

void RenderElement::operator()() {
    glBindVertexArray(vao);     get_error();
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, (void *) 0); get_error("rendering");
}