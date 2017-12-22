//
// Created by mazrog on 22/12/17.
//

#include "textRender.hpp"

//
// Created by mazrog on 21/12/17.
//

#include "textRender.hpp"

ShaderProgram TextRender::prog;

void TextRender::init() {
    if(!TextRender::prog.getProgId()) {
        TextRender::prog = ShaderProgram("sample/shaders/text_vert.glsl", "sample/shaders/text_frag.glsl");
        Text::init(prog.getProgId());
    }
}

TextRender::TextRender() :
        transform(), text() {
    TextRender::init();
}

void TextRender::setData(GUI * gui) {
    transform.loadUniform(TextRender::prog.getProgId(), "transform");
}

void TextRender::operator()(DynamicData const& dd, GuiData const& gd) {
    TextRender::prog.useProgram();

    text.write(0, 24, glm::vec2(dd.position), gd.text);
}