//
// Created by mazrog on 25/01/18.
//

#include "rendering/renderPass.hpp"

RenderPass::RenderPass(RenderGroup * renderGroup, VoidFunc const& prepareFunction)
        : prepareFunc(prepareFunction), group(renderGroup) {}

RenderPass::~RenderPass() {}

void RenderPass::prepare() {
    fbo->bind();
    prepareFunc();
}

void RenderPass::render(Camera *) {
    prepare();
    /* Other stuff */
    group->render();
}