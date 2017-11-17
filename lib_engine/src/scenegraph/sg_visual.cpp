//
// Created by mazrog on 13/11/17.
//

#include "scenegraph/sg_visual.hpp"


void SGV::render(){
    for (auto& node : nodes){
        node->render();
    }
}