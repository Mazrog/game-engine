//
// Created by mazrog on 13/11/17.
//

#include <engine.hpp>
#include "scenegraph/sg_logic.hpp"


/* SGL_Node class */

SGL_Node::SGL_Node(int draw_order) :
        draw_order(draw_order), model(new Model()) {}

SGL_Node::SGL_Node(const char * model_name, int dr_order) :
        draw_order(dr_order) {
    model = Engine::engine.get_controller().get_current_state()->get_models().at(model_name);
}

SGL_Node::~SGL_Node() {}

bool SGL_Node::operator<(SGL_Node && b) { return draw_order < b.draw_order; }

/* SGL      class */

SGL::SGL() : current_camera(0) {}

SGL::~SGL() {
    clear();
}

void SGL::bind(SG_NODE_TYPE type, const char * name, SGL_Node * node) {
    if(graph.find(name) == graph.end()) {
        switch (type) {
            case SG_NODE_TYPE::SG_CAMERA:
                cameras.push_back(static_cast<Camera *>(node));
            case SG_NODE_TYPE::SG_LIGHT:
            case SG_NODE_TYPE::SG_STATIC:
            case SG_NODE_TYPE::SG_DYNAMIC:
                graph[name] = node;
                nodes[type].push_back(node);
                rendering_order.insert(node);
                break;
            case SG_NODE_TYPE::SG_FORCE:;
        }
    }
}

void SGL::clear() {
    cameras.clear();
    nodes.clear();
    graph.clear();
    rendering_order.clear();
    current_camera = 0;
}