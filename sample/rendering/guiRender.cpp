//
// Created by mazrog on 21/12/17.
//

#include <iostream>
#include <base.hpp>

#include "display.hpp"
#include "guiRender.hpp"

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

    Model * model = gui->get_model();

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());
    vao.linkDataAttribute(1, 2, sizeof(glm::vec2) * model->uvs.size(), model->uvs.data());

    texture.loadUniform(prog.getProgId(), "gui_texture");
    texture.loadImageToVram("sample/img/gui/box.png");
    texture.send(0);

    model->clear();
}

void GuiRender::operator()(DynamicData const& dd) {
    prog.useProgram();
    vao.bind();
    transform.send(dd.transform);
    texture.send(0);

    glDisable(GL_DEPTH_TEST);
    glDrawArrays(GL_TRIANGLES, 0, 6); get_error("render gui");
    glEnable(GL_DEPTH_TEST);
}