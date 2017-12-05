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
        vao(), transform(), texture() {}

void RenderEntity::setData(SGL_Node * node) {
    transform.loadUniform(prog.getProgId(), "transform");

    Model& model = node->get_model();

    if(!model.links.empty()) {
        vao.linkElementDataAttribute(sizeof(GLuint) * model.links.size(), model.links.data());
        renderConfig.is_element = true;
    }

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model.vertices.size(), model.vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model.uvs.size(), model.uvs.data());
    vao.linkDataAttribute(2, 3, sizeof(glm::vec3) * model.normals.size(), model.normals.data());


    texture.loadUniform(prog.getProgId(), "texture_entity");
    texture.loadImageToVram("sample/img/terrain_texture.png");
    texture.send(0);

    unsigned long count = model.links.size();
    renderConfig.count = count ? count : model.vertices.size();

    model.clear();
}

void RenderEntity::operator()(DynamicData const& dd) {
    vao.bind();

    transform.send(dd.tranform);
    texture.send(0);

    if(renderConfig.is_element) {
        glDrawElements(renderConfig.primitive, renderConfig.count, GL_UNSIGNED_INT, (void *) 0);
        get_error("render entity");
    } else {
        glDrawArrays(renderConfig.primitive, 0, renderConfig.count);
        get_error("render entity");
    }
}