//
// Created by mazrog on 22/12/17.
//

#ifndef ENGINE_TEXTRENDER_HPP
#define ENGINE_TEXTRENDER_HPP

#include <rendering/renderer.hpp>
#include <gui/gui.hpp>
#include <gui/text.hpp>

class TextRender {
public:
    static void init();
    static ShaderProgram    prog;

public:
    TextRender();
    ~TextRender() = default;

    void setData(GUI * gui);

    void operator()( DynamicData const& dd, GuiData & gd );

private:
    Uniform         transform;
    Uniform         font_color;
    Text            text;
};


#endif //ENGINE_TEXTRENDER_HPP
