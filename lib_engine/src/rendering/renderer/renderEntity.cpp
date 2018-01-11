//
// Created by mazrog on 14/11/17.
//

#include <iostream>

#include "display.hpp"
#include "rendering/renderer/renderEntity.hpp"

ShaderProgram RenderEntity::prog;

void RenderEntity::init() {
    if(!RenderEntity::prog.getProgId()) {
        RenderEntity::prog = ShaderProgram("sample/shaders/vert.glsl", "sample/shaders/frag.glsl");
    }
}

RenderEntity::RenderEntity() :
        vao(), transform(), texture() {
    RenderEntity::init();
}

void RenderEntity::setData(SGL_Node * node) {
    transform.loadUniform(prog.getProgId(), "transform");

    const Model * model = node->get_model();

    if(!model->links.empty()) {
        vao.linkElementDataAttribute(sizeof(GLuint) * model->links.size(), model->links.data());
    }

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model->uvs.size(), model->uvs.data());
    vao.linkDataAttribute(2, 3, sizeof(glm::vec3) * model->normals.size(), model->normals.data());


    texture.loadUniform(prog.getProgId(), "entity_texture");

    for( auto const& pair: model->mtlLib ) {
        pair.second->map_indexes[1] = texture.loadImageToVram(pair.second->map_Kd.c_str(), GL_RGBA, GL_BGRA_EXT);
    }

    unsigned long count = model->links.size();
    renderConfig.count = count ? count : model->vertices.size();

    mtlLib = model->mtlLib;
}

void RenderEntity::operator()(DynamicData const& dd) {
    RenderEntity::prog.useProgram();
    vao.bind();
    transform.send(dd.transform);

    for( auto const& pair : mtlLib ) {
        texture.send(pair.second->map_indexes[1], 0);
        for( auto const& vert_info : pair.second->vert_infos ) {
            glDrawArrays(renderConfig.primitive, vert_info.first, vert_info.second);
            get_error("render entity");
        }
    }
}