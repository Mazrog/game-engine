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
        vao(), transform(), texture() {
    RenderEntity::init();
}

void RenderEntity::setData(SGL_Node * node) {
    transform.loadUniform(prog.getProgId(), "transform");

    Model * model = node->get_model();

    if(!model->links.empty()) {
        vao.linkElementDataAttribute(sizeof(GLuint) * model->links.size(), model->links.data());
        renderConfig.is_element = true;
    }

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model->uvs.size(), model->uvs.data());
    vao.linkDataAttribute(2, 3, sizeof(glm::vec3) * model->normals.size(), model->normals.data());


    texture.loadUniform(prog.getProgId(), "texture_entity");

    for( auto const& pair: model->mtlLib ) {
        pair.second->map_indexes[1] = texture.loadImageToVram(pair.second->map_Kd.c_str(), GL_RGBA, GL_BGRA_EXT);
    }

    unsigned long count = model->links.size();
    renderConfig.count = count ? count : model->vertices.size();

    mtlLib = std::move(model->mtlLib);

    model->clear();
}

void RenderEntity::operator()(DynamicData const& dd) {
    RenderEntity::prog.useProgram();
    vao.bind();
    transform.send(dd.transform);

    if(renderConfig.is_element) {
        for( auto const& pair : mtlLib ) {
            for( auto const& vert_info : pair.second->vert_infos ) {
                glDrawElements(renderConfig.primitive, vert_info.first, GL_UNSIGNED_INT, (void *) 0);
                get_error("render entity");
            }
        }
    } else {
        for( auto const& pair : mtlLib ) {
            texture.send(pair.second->map_indexes[1], 0);
            for( auto const& vert_info : pair.second->vert_infos ) {
                glDrawArrays(renderConfig.primitive, vert_info.first, vert_info.second);
                get_error("render entity");
            }
        }
    }
}