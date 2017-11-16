//
// Created by mazrog on 13/11/17.
//

#include <iostream>

#include "scenegraph/sg_visual.hpp"

SGV::SGV() = default;

void SGV::render(){
    for (auto& node : nodes){
        node->render();
    }
}