//
// Created by mazrog on 14/11/17.
//

#ifndef ENGINE_RENDERELEMENT_HPP
#define ENGINE_RENDERELEMENT_HPP

#include <GL/glew.h>

#include <rendering/structs/vao.hpp>
#include <scenegraph/sg_logic.hpp>
#include <rendering/renderer.hpp>
#include <rendering/program.hpp>
#include <rendering/texture.hpp>


class RenderEntity : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    RenderEntity();
    ~RenderEntity() = default;

    void setData(SGL_Node * node);

    void operator()( DynamicData const& dd ) override;

private:
    Vao             vao;

    Uniform         transform;
    Texture         texture;

    MtlLib          mtlLib;
};


#endif //ENGINE_RENDERELEMENT_HPP
