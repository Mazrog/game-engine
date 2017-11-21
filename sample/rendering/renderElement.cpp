//
// Created by mazrog on 14/11/17.
//

#include <iostream>
#include <rendering/program.hpp>

#include "display.hpp"
#include "renderElement.hpp"

ShaderProgram RenderElement::prog;

void RenderElement::init() {
    if(!RenderElement::prog.getProgId()) {
        RenderElement::prog = ShaderProgram("sample/shaders/vert.glsl", "sample/shaders/frag.glsl");
    }
}

RenderElement::RenderElement() : vao(), vbos(), transform_loc() {}

RenderElement::RenderElement(SGL_Node * node) {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error();
    glBindVertexArray(vao);     get_error();

    glGenBuffers(3, vbos);      get_error();

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]); get_error();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * rd.links->size(), rd.links->data(), GL_STATIC_DRAW); get_error();

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error();

    glEnableVertexAttribArray(0); get_error();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error();


    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); get_error();
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.uvs->size(), rd.uvs->data(), GL_STATIC_DRAW); get_error();

    glEnableVertexAttribArray(10); get_error();
    glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error();


    /* TODO : WRAP TEXTURE ! */
    GLuint faceCube;
    SDL_Surface * surf = IMG_Load("sample/img/crate.jpg");

    glGenTextures(1, &faceCube); get_error();
    glBindTexture(GL_TEXTURE_2D, faceCube); get_error();
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels); get_error();
    SDL_FreeSurface(surf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error();

    GLint textCubeLoc = glGetUniformLocation(prog.getProgId(), "textCube"); get_error();
    glActiveTexture(GL_TEXTURE0); get_error();
    glUniform1i(textCubeLoc, 0); get_error();

    /* TO BE WRAPPED */
    transform_loc = glGetUniformLocation(prog.getProgId(), "transform"); get_error();
}

void RenderElement::operator()(DynamicData const& dd) {
    prog.useProgram();
    glBindVertexArray(vao);     get_error();

    glUniformMatrix4fv(transform_loc, 1, GL_FALSE, glm::value_ptr(*dd.tranform)); get_error();

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *) 0); get_error();
}