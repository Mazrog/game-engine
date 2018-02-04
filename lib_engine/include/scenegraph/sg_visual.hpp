//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_SG_VISUAL_HPP
#define ENGINE_SG_VISUAL_HPP

#include "sg_logic.hpp"
#include "gui/guiManager.hpp"
#include "rendering/renderPass.hpp"

class SGV {
public:
    SGV(SGL * sgl, GuiManager * guiManager);

    void render();
    void clear();

    /* Attributs */
    RenderPasses              renderPasses;
    Camera                  * camera;
    std::vector<GUI *>        guis;
};

#endif //ENGINE_SG_VISUAL_HPP
