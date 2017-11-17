//
// Created by mazrog on 13/11/17.
//

#include <engine.hpp>
#include "scenegraph/sg_logic.hpp"


/* SGL      class */

SGL::SGL() = default;

void SGL::bind(SG_NODE_TYPE type, const char * name, SGL_Node * node) {
    switch (type){
        case SG_NODE_TYPE::SG_CAMERA:
            cameras.push_back(static_cast<Camera *>(node));
        case SG_NODE_TYPE::SG_STATIC:
        case SG_NODE_TYPE::SG_DYNAMIC:
            graph[name] = node;
            nodes[type].push_back(node);
            rendering_order.insert(node);
            break;
        case SG_NODE_TYPE::SG_FORCE:;
    }
}

/* SGL_Node class */

SGL_Node::SGL_Node(unsigned draw_order) : draw_order(draw_order) {}

bool SGL_Node::operator<(SGL_Node && b) {
    return draw_order < b.draw_order;
}