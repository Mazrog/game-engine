//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_SIMPLERENDER_HPP
#define ENGINE_SIMPLERENDER_HPP

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer.hpp"

class SimpleRender : public Renderer {
public:
    static void init();

public:
    SimpleRender() = default;
    explicit SimpleRender(SGL_Node * node);
    void operator() ( ) override;

private:
    GLuint          vao;
    GLuint          vbos[2];
};


#endif //ENGINE_SIMPLERENDER_HPP
