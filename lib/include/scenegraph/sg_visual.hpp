//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_VISUAL_HPP
#define ENGINE_SG_VISUAL_HPP

#include "sg_logic.hpp"
#include "rendering/camera.hpp"

class SGV {
public:
    SGV();

    void render();

    /* Attributs */
    std::vector<SGL_Node *>     nodes;
};


#endif //ENGINE_SG_VISUAL_HPP
