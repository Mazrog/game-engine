//
// Created by mazrog on 14/11/17.
//

#ifndef ENGINE_RENDERELEMENT_HPP
#define ENGINE_RENDERELEMENT_HPP

#include <GL/glew.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer.hpp"
#include "rendering/program.hpp"


class RenderEntity : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    RenderEntity();
    explicit RenderEntity(SGL_Node * node);

    ~RenderEntity() = default;

    void operator()( DynamicData const& dd ) override;

private:
    GLuint          vao;
    GLuint          vbos[4];

    Uniform         transform;
    Uniform         texture;
};


#endif //ENGINE_RENDERELEMENT_HPP
