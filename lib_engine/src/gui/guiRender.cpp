//
// Created by mazrog on 21/12/17.
//

#include <iostream>
#include <base.hpp>

#include "display.hpp"
#include "gui/guiRender.hpp"

ShaderProgram GuiRender::prog;

void GuiRender::init() {
    if(!GuiRender::prog.getProgId()) {
        GuiRender::prog = ShaderProgram("sample/shaders/gui_vert.glsl", "sample/shaders/gui_frag.glsl");
    }
}

GuiRender::GuiRender() :
        vao(), transform(), texture() {
    GuiRender::init();
}

void GuiRender::setData(GUI * gui) {
    transform.loadUniform(prog.getProgId(), "transform");
    anchor = gui->get_anchor();

    Model * model = gui->get_model();

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model->uvs.size(), model->uvs.data());

    TextureFormat const& tf = gui->get_textureFormat();
    if ( tf.texturePath ) {
        texture.loadUniform(prog.getProgId(), "gui_texture");
        texture.loadImageToVram(tf.texturePath, tf.internal_format, tf.format);
        texture.send(0);
    }
}

void GuiRender::operator()(DynamicData const& dd) {
    GuiRender::prog.useProgram();
    vao.bind();
    transform.send(dd.transform);
    if ( texture.isActive() ) { texture.send(0); }

    glDrawArrays(GL_TRIANGLES, 0, 6); get_error("render gui");
}

