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
    current_camera = 0;
}

void SGV::render(){
    if(!nodes.empty()) {
        /* Sending the current camera information to the programs */
        if (current_camera < cameras->size()) {
            cameras->at(current_camera)->render();
        }

        /* Then rendering all the static and dynamic nodes following the rendering order */
        for (auto &node : nodes) {
            node->render();
        }

        /* Rendering GUIs */
        for(auto & gui : guis) {
            gui->render();
        }
    }
}