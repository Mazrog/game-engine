//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_VISUAL_HPP
#define ENGINE_SG_VISUAL_HPP

#include "sg_logic.hpp"
#include "rendering/camera.hpp"


class SGV {
public:
    SGV(SGL * const& sgl);

    void render();
    void clear();

    /* Attributs */
    std::vector<SGL_Node *>      nodes;
    unsigned                     current_camera;
    std::vector<Camera *>      * cameras;
};


#endif //ENGINE_SG_VISUAL_HPP
