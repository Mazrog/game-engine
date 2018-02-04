//
// Created by mazrog on 25/01/18.
//

#ifndef ENGINE_RENDERGROUP_HPP
#define ENGINE_RENDERGROUP_HPP

#include <map>
#include "scenegraph/sg_logic.hpp"

class RenderGroup {
public:
    RenderGroup();
    ~RenderGroup();

    void add(const char * name, SGL_Node * node);

    void render();

private:
    EntityGroup     group;
};


#endif //ENGINE_RENDERGROUP_HPP
