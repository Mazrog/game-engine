//
// Created by mazrog on 25/01/18.
//

#ifndef ENGINE_RENDERPASS_HPP
#define ENGINE_RENDERPASS_HPP

#include "renderGroup.hpp"
#include "structs/fbo.hpp"

class RenderPass {
public:
    RenderPass();
    ~RenderPass();

    void prepare();
    void render();

private:
    RenderGroup group;
};


#endif //ENGINE_RENDERPASS_HPP
