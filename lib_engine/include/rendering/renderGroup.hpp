//
// Created by mazrog on 25/01/18.
//

#ifndef ENGINE_RENDERGROUP_HPP
#define ENGINE_RENDERGROUP_HPP

#include <map>
#include "scenegraph/sg_logic.hpp"

using EntityGroup = std::map<std::string, SGL_Node *>;


class RenderGroup {
public:
    RenderGroup();
    ~RenderGroup();

    void bind();

private:
    EntityGroup     group;
};


#endif //ENGINE_RENDERGROUP_HPP
