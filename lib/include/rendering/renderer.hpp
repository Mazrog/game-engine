//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include "scenegraph/sg_logic.hpp"

class Renderer {
protected:
    virtual void operator() ( ) = 0;
};


#endif //ENGINE_RENDERER_HPP
