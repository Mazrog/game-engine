//
// Created by mazrog on 13/11/17.
//

#include <engine.hpp>
#include "scenegraph/sg_logic.hpp"
#include "rendering/camera.hpp"


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

SGL::SGL() : renderGroup(), renderPasses(), camera(nullptr) {
    /* Initialise one render group by default */
    RenderGroup * rg = new RenderGroup();
    renderGroup.push_back(rg);
    renderPasses.push_back(new RenderPass(rg));
}

SGL::~SGL() {
    clear();
}

void SGL::bind(SG_NODE_TYPE type, const char *name, SGL_Node *node, unsigned renderGroupID) {
    switch (type) {
        case SG_NODE_TYPE::SG_CAMERA:
            if ( !camera ) {
                camera = dynamic_cast<Camera *>(node);
            } else { throw std::runtime_error("Binding camera : another camera already exists."); }
        case SG_NODE_TYPE::SG_LIGHT:
            renderGroup.at(0)->add(name, node);
            break;
        case SG_NODE_TYPE::SG_STATIC:
        case SG_NODE_TYPE::SG_DYNAMIC:
            if( name && *name ) {
                auto it = graph.find(name);
                if (it == graph.end()) { graph[name] = node; }
                else { throw std::runtime_error("Binding node to the scenegraph : duplicate name."); }
            }

            if ( renderGroupID < renderGroup.size() ) {
                renderGroup.at(renderGroupID)->add(name, node);
            } else { throw std::runtime_error("Binding node : render group ID out of bound"); }

            break;
    }
}

void SGL::addRenderPass(RenderPass *renderPass) {
    renderPasses.push_back(renderPass);
}

void SGL::makeRenderPass(VoidFunc const &prepareFunction) {
    renderPasses.push_back(new RenderPass(nullptr, prepareFunction));
}

void SGL::setRenderPassPrepareFunction(unsigned id, VoidFunc const &prepareFunction) {
    if( id < renderPasses.size() ) {
        renderPasses.at(id)->setRenderPrepareFunction(prepareFunction);
    } else {
        throw std::runtime_error("Setting Prepare Function : index out of bound");
    }
}

void SGL::setRenderPassRenderGroup(unsigned idPass, unsigned idGroup) {
    if ( idPass < renderPasses.size() ) {
        if ( idGroup < renderGroup.size() ) {
            renderPasses.at(idPass)->setRenderGroup(renderGroup.at(idGroup));
        } else { throw std::runtime_error("Setting Render group to Render pass : group id out of bound."); }
    } else { throw std::runtime_error("Setting Render group to Render pass : pass id out of bound."); }
}

void SGL::clear() {
    for( auto & rg : renderGroup ) {
        delete rg;
    }
    renderGroup.clear();
}