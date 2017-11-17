//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_LOGIC_HPP
#define ENGINE_SG_LOGIC_HPP

#include <set>

#include "scenegraph.hpp"

/* Forward declarations */
class Camera;


/* --------------------- */

class SGL_Node {
public:
    SGL_Node();
    virtual ~SGL_Node() = default;

    virtual void render() = 0;
    RenderingData&  get_rendering_data() { return renderingData; }
    DynamicData&    get_dynamic_data() { return dynamicData; }


    bool operator<(SGL_Node && b);

protected:
    int             draw_order; /* Draw order for the rendering */
    RenderingData   renderingData;
    DynamicData     dynamicData;
};



class SGL {
public:
    SGL();

    void bind(SG_NODE_TYPE type, const char * name, SGL_Node * node);

    /* Attributs */
    std::vector<Camera *>                           cameras;
    std::map<const char *, SGL_Node *>              graph;
    std::map<SG_NODE_TYPE, std::vector<SGL_Node *>> nodes;
    std::set<SGL_Node *>                            rendering_order;
};


#endif
