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
    static ShaderProgram    prog;

public:
    SimpleRender();
    explicit SimpleRender(SGL_Node * node);
    void operator() ( DynamicData const& dd ) override;

private:
//    glm::mat4 *       transform;

    GLuint          vao;
    GLuint          vbos[2];
    GLint           transform_loc;
};


#endif //ENGINE_SIMPLERENDER_HPP
