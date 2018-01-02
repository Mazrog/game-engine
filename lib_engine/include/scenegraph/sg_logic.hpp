//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_LOGIC_HPP
#define ENGINE_SG_LOGIC_HPP

#include <set>

#include "scenegraph.hpp"
#include "rendering/model.hpp"

/* Forward declarations */
class Camera;
class SGL;

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



class SGL {
public:
    SGL();
    ~SGL();

    void bind(SG_NODE_TYPE type, const char * name, SGL_Node * node);
    void load_model(const char * tag, const char * file);

    void clear();

    /* Attributs */
    unsigned                                        current_camera;

    std::vector<Camera *>                           cameras;

    std::map<std::string, SGL_Node *>               graph;
    std::map<SG_NODE_TYPE, std::vector<SGL_Node *>> nodes;
    std::set<SGL_Node *>                            rendering_order;
};


#endif
