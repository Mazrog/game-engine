//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_LOGIC_HPP
#define ENGINE_SG_LOGIC_HPP

#include <set>
#include <functional>

#include "scenegraph.hpp"
#include "rendering/model.hpp"

/* Forward declarations */
class Camera;
class SGL;
class RenderPass;
class RenderGroup;
/* --------------------- */

class SGL_Node {
public:
    SGL_Node(int dr_order = 1);
    SGL_Node(const char * model, int dr_order = 1);
    virtual ~SGL_Node();

    virtual void render() = 0;

    virtual void move() {};

    Model *  get_model() { return model; }
    DynamicData&    get_dynamic_data() { return dynamicData; }


    bool operator<(SGL_Node && b);

protected:
    int               draw_order; /* Draw order for the rendering */
    Model           * model;
    DynamicData       dynamicData;
};

/* Usings */
using VoidFunc = std::function<void()>;
using RenderPasses = std::vector<RenderPass *>;
using EntityGroup = std::map<std::string, SGL_Node *>;
/* --------------------- */

class SGL {
public:
    SGL();
    ~SGL();

    void bind(SG_NODE_TYPE type, const char * name, SGL_Node * node, unsigned renderGroupID);
    void load_model(const char * tag, const char * file);

    /* We either add a complete renderPass */
    void addRenderPass(RenderPass * renderPass);

    /* Or we build one in place and fill it afterwards */
    void makeRenderPass(VoidFunc const& prepareFunction);
    void setRenderPassPrepareFunction(unsigned id, VoidFunc const& prepareFunction);
    void setRenderPassRenderGroup(unsigned idPass, unsigned idGroup);

    void clear();

    /* Attributs */
    std::vector<RenderGroup *>    renderGroup;
    RenderPasses                  renderPasses;
    Camera                      * camera;
    EntityGroup                   graph;
};


#endif
