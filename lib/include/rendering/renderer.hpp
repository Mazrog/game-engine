//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_RENDERER_HPP
#define ENGINE_RENDERER_HPP

#include "scenegraph/sg_logic.hpp"
#include "program.hpp"

class Renderer {
public:
    static ShaderProgram        prog;

protected:
    virtual void operator() ( ) = 0;
};


#endif //ENGINE_RENDERER_HPP
