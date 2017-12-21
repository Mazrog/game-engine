//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUIRENDER_HPP
#define ENGINE_GUIRENDER_HPP

#include <GL/glew.h>

#include <rendering/structs/vao.hpp>
#include <rendering/renderer.hpp>
#include <rendering/program.hpp>
#include <rendering/texture.hpp>

#include <gui/gui.hpp>


class GuiRender : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    GuiRender();
    ~GuiRender() = default;

    void setData(GUI * gui);

    void operator()( DynamicData const& dd ) override;

private:
    Vao             vao;

    Uniform         transform;
    Texture         texture;
};


#endif //ENGINE_GUIRENDER_HPP
