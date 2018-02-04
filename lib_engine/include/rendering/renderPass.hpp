//
// Created by mazrog on 25/01/18.
//

#ifndef ENGINE_RENDERPASS_HPP
#define ENGINE_RENDERPASS_HPP

#include <functional>
#include "renderGroup.hpp"
#include "structs/fbo.hpp"

class RenderPass {
public:
    RenderPass(RenderGroup * renderGroup = nullptr, VoidFunc const& prepareFunction = [] {});
    ~RenderPass();

    void prepare();
    void render(Camera * camera);

    void setRenderGroup(RenderGroup * renderGroup) { group = renderGroup; }
    void setRenderPrepareFunction(VoidFunc const& prepareFunction) { prepareFunc = prepareFunction; }

private:
    VoidFunc prepareFunc;

    RenderGroup     * group;
    Fbo             * fbo;
};


#endif //ENGINE_RENDERPASS_HPP
