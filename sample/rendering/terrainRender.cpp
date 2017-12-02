//
// Created by mazrog on 21/11/17.
//

#include <iostream>
#include <IL/il.h>
#include "utils.hpp"
#include "terrainRender.hpp"

ShaderProgram TerrainRenderer::prog;

void TerrainRenderer::init() {
    if(!TerrainRenderer::prog.getProgId()) {
        TerrainRenderer::prog = ShaderProgram("sample/shaders/terrain_vert.glsl", "sample/shaders/terrain_frag.glsl");
    }
}

TerrainRenderer::TerrainRenderer() : vao(), vbos(), transform() {}

TerrainRenderer::TerrainRenderer(SGL_Node *node) :
        transform(prog.getProgId(), "transform"), texture(prog.getProgId(), "terrain_texture") {
    Model& model = node->get_model();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(4, vbos);      get_error("gen buffer");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]); get_error("bind buffer element");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * model.links.size(), model.links.data(), GL_STATIC_DRAW); get_error("buffer element data");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer vertices");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model.vertices.size(), model.vertices.data(), GL_STATIC_DRAW); get_error("buffer data");

    /* Coordinates */
    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 0");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]); get_error("bind buffer uvs");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * model.uvs.size(), model.uvs.data(), GL_STATIC_DRAW); get_error("buffer data uvs");

    /* UVS */
    glEnableVertexAttribArray(1); get_error("enable pointer 1");
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 1");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); get_error("bind buffer normals");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * model.normals.size(), model.normals.data(), GL_STATIC_DRAW); get_error("buffer data normals");


    /* Normals */
    glEnableVertexAttribArray(2); get_error("enable pointer 2");
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 2");



    /* TODO : WRAP TEXTURE ! */
    GLuint terrain_texture;
    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage("sample/img/terrain.png");
    ILubyte * surf = ilGetData();


    glGenTextures(1, &terrain_texture); get_error("gen texture");
    glBindTexture(GL_TEXTURE_2D, terrain_texture); get_error("bind texture");
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 GL_RGB, GL_UNSIGNED_BYTE, surf);
    get_error("tex image 2D");

    ilDeleteImage(src);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");


    glActiveTexture(GL_TEXTURE0); get_error("active texture 0");
    texture.send(0);

    renderConfig.count = model.links.size();
}

void TerrainRenderer::operator()(DynamicData const &dd) {
    glBindVertexArray(vao); get_error("bind vao render");
    transform.send(dd.tranform);

    glDrawElements(GL_TRIANGLES, renderConfig.count, GL_UNSIGNED_INT, (void *) 0); get_error("rendering terrain");
}