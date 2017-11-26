//
// Created by mazrog on 21/11/17.
//

#include <iostream>
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
        transform(prog.getProgId(), "transform") {
    RenderingData& rd = node->get_rendering_data();

    glGenVertexArrays(1, &vao); get_error("gen vao");
    glBindVertexArray(vao);     get_error("bind vao");

    glGenBuffers(4, vbos);      get_error("gen buffer");

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbos[3]); get_error("bind buffer element");
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * rd.links->size(), rd.links->data(), GL_STATIC_DRAW); get_error("buffer element data");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[0]); get_error("bind buffer vertices");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.vertices->size(), rd.vertices->data(), GL_STATIC_DRAW); get_error("buffer data");

    /* Coordinates */
    glEnableVertexAttribArray(0); get_error("enable pointer 0");
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 0");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[1]); get_error("bind buffer uvs");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * rd.uvs->size(), rd.uvs->data(), GL_STATIC_DRAW); get_error("buffer data uvs");

    /* UVS */
    glEnableVertexAttribArray(1); get_error("enable pointer 1");
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 1");

    glBindBuffer(GL_ARRAY_BUFFER, vbos[2]); get_error("bind buffer normals");
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * rd.normals->size(), rd.normals->data(), GL_STATIC_DRAW); get_error("buffer data normals");


    /* Normals */
    glEnableVertexAttribArray(2); get_error("enable pointer 2");
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0); get_error("set pointer 2");
}

void TerrainRenderer::operator()(DynamicData const &dd) {
    glBindVertexArray(vao); get_error("bind vao render");
    transform.send(*dd.tranform);

    glDrawElements(GL_TRIANGLES, 2400, GL_UNSIGNED_INT, (void *) 0); get_error("rendering terrain");
}