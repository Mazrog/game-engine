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

TerrainRenderer::TerrainRenderer() : vao(), transform(), texture() {
    TerrainRenderer::init();
}

TerrainRenderer::~TerrainRenderer() {}

TerrainRenderer& TerrainRenderer::operator=(TerrainRenderer && tr) {
    vao = std::move(tr.vao);

    transform = std::move(tr.transform);
    texture = std::move(tr.texture);
    renderConfig = tr.renderConfig;
    return *this;
}

void TerrainRenderer::setData(SGL_Node *node) {
    transform.loadUniform(prog.getProgId(), "transform");

    Model * model = node->get_model();

    vao.linkElementDataAttribute(sizeof(GLuint) * model->links.size(), model->links.data());

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model->uvs.size(), model->uvs.data());
    vao.linkDataAttribute(2, 3, sizeof(glm::vec3) * model->normals.size(), model->normals.data());

    texture.loadUniform(prog.getProgId(), "terrain_texture");
//    texture.loadImageToVram("sample/img/terrain.png");
    texture.loadImageToVram("sample/img/height_map.png");
    texture.send(0);

    renderConfig.count = model->links.size();
    model->clear();
}

void TerrainRenderer::operator()(DynamicData const &dd) {
    vao.bind();
    transform.send(dd.transform);
    texture.send(0);

    glDrawElements(GL_TRIANGLES, renderConfig.count, GL_UNSIGNED_INT, (void *) 0); get_error("rendering terrain");
}