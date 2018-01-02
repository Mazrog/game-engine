//
// Created by mazrog on 01/01/18.
//

#include <base.hpp>
#include "skyboxRender.hpp"

ShaderProgram SkyboxRender::prog;

void SkyboxRender::init() {
    if(!SkyboxRender::prog.getProgId()) {
        SkyboxRender::prog = ShaderProgram("sample/shaders/skybox_vert.glsl", "sample/shaders/skybox_frag.glsl");
    }
}

SkyboxRender::SkyboxRender() :
        vao(), transform(), texture(GL_TEXTURE_CUBE_MAP) {
    SkyboxRender::init();
}

void SkyboxRender::setData(SGL_Node * node) {
    transform.loadUniform(prog.getProgId(), "transform");

    Model * model = node->get_model();

    vao.linkDataAttribute(0, 3, sizeof(glm::vec3) * model->vertices.size(), model->vertices.data());

    texture.loadUniform(prog.getProgId(), "skybox_texture");
    texture.loadCubeMapToVram("sample/img/skybox/space", GL_RGBA, GL_RGBA);
    texture.send(0);
}

void SkyboxRender::operator()(DynamicData const& dd) {
    SkyboxRender::prog.useProgram();
    vao.bind();
    transform.send(dd.transform);
    texture.send(0);

    glDrawArrays(GL_TRIANGLES, 0, 36); get_error("render entity");
}