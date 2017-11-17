//
// Created by mazrog on 13/11/17.
//

#include <engine.hpp>
#include "scenegraph/sg_logic.hpp"


/* SGL      class */

SGL::SGL() = default;

void SGL::bind(SG_NODE_TYPE type, const char * name, SGL_Node * node) {
    graph[name] = node;
    nodes[type].push_back(node);
    if(type != SG_NODE_TYPE::SG_FORCE) {
        rendering_order.insert(node);
    }
}

/* SGL_Node class */

SGL_Node::SGL_Node() : draw_order(0) {}

bool SGL_Node::operator<(SGL_Node && b) {
    return draw_order < b.draw_order;
}