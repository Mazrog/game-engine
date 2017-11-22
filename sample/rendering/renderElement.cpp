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

RenderElement::RenderElement() :
        vao(), vbos(), transform(), texture() {}

RenderElement::RenderElement(SGL_Node * node) :
        transform(prog.getProgId(), "transform"), texture(prog.getProgId(), "textCube") {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(3, vbos);      get_error("gen buffer");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[1]); get_error("bind buffer element");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * rd.links->size(), rd.links->data(), GL_STATIC_DRAW); get_error("buffer data element");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error("buffer data");

    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 0");


    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); get_error("bind buffer uvs");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.uvs->size(), rd.uvs->data(), GL_STATIC_DRAW); get_error("buffer data uvs");

    glEnableVertexAttribArray(10); get_error("enable pointer 10");
    glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 10");


    /* TODO : WRAP TEXTURE ! */
    GLuint faceCube;
    SDL_Surface * surf = IMG_Load("sample/img/crate.jpg");

    glGenTextures(1, &faceCube); get_error("gen texture");
    glBindTexture(GL_TEXTURE_2D, faceCube); get_error("bind texture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, surf->w, surf->h, 0, GL_RGB, GL_UNSIGNED_BYTE, surf->pixels); get_error("tex image 2D");
    SDL_FreeSurface(surf);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("texture param MIN");

    glActiveTexture(GL_TEXTURE0); get_error("active texture 0");
    texture.send(0);

}

void RenderElement::operator()(DynamicData const& dd) {
    glBindVertexArray(vao);     get_error("bind vao render");
    transform.send(*(dd.tranform));

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void *) 0); get_error("render element");
}