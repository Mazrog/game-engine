//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include <glm/gtc/type_ptr.hpp>

#include "scenegraph/sg_logic.hpp"
#include "program.hpp"
#include "rendering/structs/uniform.hpp"

class Renderer {
protected:
    virtual void operator() ( DynamicData const& dd ) = 0;
};


#endif //ENGINE_RENDERER_HPP
