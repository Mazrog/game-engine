//
// Created by mazrog on 25/01/18.
//

#include <iostream>
#include "rendering/renderGroup.hpp"

RenderGroup::RenderGroup() {}

RenderGroup::~RenderGroup() {
    for( auto & pair: group ) {
        delete pair.second;
    }
}

void RenderGroup::add(const char *name, SGL_Node *node) {
    auto it = group.find(name);
    if ( it == group.end() ) {
        group[name] = node;
    } else {
        std::cerr << "This name is already used in this RenderGroup : " << name << std::endl;
        throw std::runtime_error("RenderGroup Error");
    }
}

void RenderGroup::render() {
    for(auto const& pair: group) {
        pair.second->render();
    }
}
