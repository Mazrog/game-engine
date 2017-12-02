//
// Created by mazrog on 14/11/17.
//

#include <iostream>
#include <IL/il.h>

#include "display.hpp"
#include "renderEntity.hpp"
#include "rendering/program.hpp"

ShaderProgram RenderEntity::prog;

void RenderEntity::init() {
    if(!RenderEntity::prog.getProgId()) {
        RenderEntity::prog = ShaderProgram("sample/shaders/vert.glsl", "sample/shaders/frag.glsl");
    }
}

RenderEntity::RenderEntity() :
        vao(), vbos(), transform(), texture() {}

RenderEntity::RenderEntity(SGL_Node * node) :
        transform(prog.getProgId(), "transform"), texture(prog.getProgId(), "textCube") {
    Model& model = node->get_model();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(4, vbos);      get_error("gen buffer");

    if(model.links.size()) {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]);
        get_error("bind buffer element");
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned) * model.links.size(), model.links.data(),
                     GL_STATIC_DRAW);
        get_error("buffer data element");
        renderConfig.is_element = true;
    }

    /* Coordinates */
    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model.vertices.size(), model.vertices.data(), GL_STATIC_DRAW); get_error("buffer data");
    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 0");


    /* UVS */
    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]); get_error("bind buffer uvs");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * model.uvs.size(), model.uvs.data(), GL_STATIC_DRAW); get_error("buffer data uvs");
    glEnableVertexAttribArray(1); get_error("enable pointer 1");
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 1");

    /* Normals */
    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); get_error("bind buffer normals");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model.normals.size(), model.normals.data(), GL_STATIC_DRAW); get_error("buffer data normals");
    glEnableVertexAttribArray(2); get_error("enable pointer 2");
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 2");



    /* TODO : WRAP TEXTURE ! */
    GLuint faceCube;
    ilInit();
    ilLoadImage("sample/img/crate.png");
    ILubyte * surf = ilGetData();

    glGenTextures(1, &faceCube); get_error("gen texture");
    glBindTexture(GL_TEXTURE_2D, faceCube); get_error("bind texture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0, GL_RGB, GL_UNSIGNED_BYTE, surf); get_error("tex image 2D");
    ilClearImage();

    glGenerateMipmap(GL_TEXTURE_2D); get_error("mipmap");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR); get_error("mipmap linear");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");
//    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -.4f); get_error("mipmap bias");


    glActiveTexture(GL_TEXTURE0); get_error("active texture 0");
    texture.send(0);

    unsigned long count = model.links.size();
    renderConfig.count = count ? count : model.vertices.size();

    model.clear();
}

void RenderEntity::operator()(DynamicData const& dd) {
    glBindVertexArray(vao);     get_error("bind vao render");
    transform.send(dd.tranform);

    if(renderConfig.is_element) {
        glDrawElements(renderConfig.primitive, renderConfig.count, GL_UNSIGNED_INT, (void *) 0);
        get_error("render entity");
    } else {
        glDrawArrays(renderConfig.primitive, 0, renderConfig.count);
        get_error("render entity");
    }
}