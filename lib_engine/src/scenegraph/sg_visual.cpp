//
// Created by mazrog on 13/11/17.
//

#include "scenegraph/sg_visual.hpp"

SGV::SGV(s_sgl const& sgl) : /* nodes(), */
                      current_camera(sgl->current_camera),
                      cameras(&sgl->cameras) {
    for(auto const& elem : sgl->rendering_order){ nodes.push_back(elem); }
}

void SGV::render(){
    /* Sending the current camera information to the programs */
    if(current_camera < cameras->size()) {
        cameras->at(current_camera)->render();
    }

    /* Then rendering all the static and dynamic nodes following the rendering order */
    for (auto& node : nodes){
        node->render();
    }
}