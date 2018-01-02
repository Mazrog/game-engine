//
// Created by mazrog on 13/11/17.
//

#include "scenegraph/sg_visual.hpp"

SGV::SGV(SGL * const& sgl, GuiManager * guiManager) :
                      current_camera(sgl->current_camera),
                      cameras(&sgl->cameras) {
    for(auto const& elem : sgl->rendering_order){ nodes.push_back(elem); }
    for(auto const& pair : guiManager->get_guis()){ guis.push_back(pair.second); }
}

void SGV::clear() {
    nodes.clear();
    cameras->clear();
    guis.clear();
    current_camera = 0;
}

void SGV::render(){
    if(!nodes.empty()) {
        /* Sending the current camera information to the programs */
        if (current_camera < cameras->size()) {
            cameras->at(current_camera)->render();
        }

        glEnable(GL_DEPTH_TEST); get_error("enable depth");
        glEnable(GL_CULL_FACE); get_error("enable cull");
        glCullFace(GL_BACK); get_error("cull both");
        /* Then rendering all the static and dynamic nodes following the rendering order */
        for (auto &node : nodes) {
            node->render();
        }
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