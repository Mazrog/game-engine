//
// Created by mazrog on 12/11/17.
//

#include "engine.hpp"
#include "simpleRender.hpp"
#include "rendering/program.hpp"
#include "display.hpp"

ShaderProgram SimpleRender::prog;

void SimpleRender::init() {
    if(!SimpleRender::prog.getProgId()) {
        SimpleRender::prog = ShaderProgram("sample/shaders/vert.glsl", "sample/shaders/frag.glsl");
    }
}

SimpleRender::SimpleRender() : vao(), vbos(), transform_loc() {}

SimpleRender::SimpleRender(SGL_Node * node) {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error();
    glBindVertexArray(vao);     get_error();

    glGenBuffers(2, vbos);      get_error();
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error();

    glEnableVertexAttribArray(0); get_error();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) 0); get_error();

    glEnableVertexAttribArray(1); get_error();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *) (3*sizeof(float))); get_error();


    /* TO BE WRAPPED */
    transform_loc = glGetUniformLocation(prog.getProgId(), "transform"); get_error("k");
}

void SimpleRender::operator()(DynamicData const& dd) {
    prog.useProgram();
    glBindVertexArray(vao);     get_error();

    /* Sending uniforms if they have changed */
    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(*dd.tranform)); get_error();

    glDrawArrays(GL_TRIANGLES, 0, 3); get_error("rendering");
}