//
// Created by mazrog on 22/12/17.
//

#include <engine.hpp>
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
        transform(), font_color(), text() {
    TextRender::init();
}

void TextRender::setData(GUI * gui) {
    transform.loadUniform(TextRender::prog.getProgId(), "transform");
    font_color.loadUniform(TextRender::prog.getProgId(), "font_color");
}

void TextRender::operator()(DynamicData const& dd, GuiData & gd) {
    TextRender::prog.useProgram();

    auto end = gd.guiContent.end();
    glm::vec2 dimension = glm::vec2(2.f * dd.scale);

    Display& display = Engine::engine.get_display();
//    float sx = 2.f / display.get_windowWidth();
    float sy = 2.f / display.get_windowHeight();

    Dimension dim = {0, 0};
    Point position = gd.anchor;

    /* Rendering the title of the window, if any */
    auto it = gd.guiContent.find("title");
    if ( it != end ) {
        dim = text.preview_text(0, it->second->font_size, it->second->text);

        position.x = position.x + dimension.x / 2.f - dim.x / 2.f;
        position.y = position.y - ((it->second->font_size + 3) * sy);

        font_color.send(it->second->font_color);
        text.write(0, it->second->font_size, position, it->second->text);
    }

    position.y -= dim.y;

    it = gd.guiContent.find("content");
    if ( it != end ) {
        dim = text.preview_text(0, it->second->font_size, it->second->text);

        font_color.send(it->second->font_color);
        text.write(0, it->second->font_size, position, it->second->text);
    }
    gd.dimension = dim;
}
