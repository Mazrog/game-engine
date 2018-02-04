//
// Created by mazrog on 13/11/17.
//

#include "scenegraph/sg_visual.hpp"

SGV::SGV(SGL * sgl, GuiManager * guiManager) : renderPasses(sgl->renderPasses), camera(sgl->camera) {
    for(auto const& pair : guiManager->get_guis()){ guis.push_back(pair.second); }
}

void SGV::clear() {
    guis.clear();
    renderPasses.clear();
}

void SGV::render(){
    glEnable(GL_DEPTH_TEST); get_error("enabling depth test");
    for(auto const& renderPass: renderPasses) {
        renderPass->render(camera);
    }

    if ( !guis.empty() ) {
        glDisable(GL_DEPTH_TEST); get_error("disable depth test");
        glDisable(GL_CULL_FACE);  get_error("disable cull face");
        glEnable(GL_BLEND); get_error("enable blend");
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); get_error("blend func");
        /* Rendering GUIs */
        for(auto & gui : guis) {
            gui->build_guiData();
            gui->render();
        }
        glDisable(GL_BLEND);
    }
}