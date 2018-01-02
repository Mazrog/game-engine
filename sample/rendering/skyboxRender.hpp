//
// Created by mazrog on 01/01/18.
//

#ifndef ENGINE_SKYBOXRENDER_HPP
#define ENGINE_SKYBOXRENDER_HPP

#include <rendering/renderer.hpp>
#include <rendering/structs/vao.hpp>
#include <rendering/texture.hpp>

class SkyboxRender : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    SkyboxRender();
    ~SkyboxRender() = default;

    void setData(SGL_Node * node);

    void operator()( DynamicData const& dd ) override;

private:
    Vao             vao;

    Uniform         transform;
    Texture         texture;
};


#endif //ENGINE_SKYBOXRENDER_HPP
