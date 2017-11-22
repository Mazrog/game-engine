//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PROCEDURAL_HPP
#define ENGINE_PROCEDURAL_HPP

#include <GL/glew.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer.hpp"
#include "rendering/uniform.hpp"

class Procedural : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    Procedural();
    explicit Procedural(SGL_Node * node);

    ~Procedural() = default;

    void operator()( DynamicData const& dd ) override;
    void operator()(DynamicData const& dd, GLenum primitive);

private:
    GLuint          vao;
    GLuint          vbos[2];

    Uniform         transform;
    Uniform         y_max;
};


#endif //ENGINE_PROCEDURAL_HPP
