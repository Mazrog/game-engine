//
// Created by mazrog on 06/01/18.
//

#include "button.hpp"

Button::Button(std::string const &tag, std::wstring const &text, const char *texturePath, glm::vec2 const &position,
               glm::vec2 const &dimension, unsigned fontSize,
               glm::vec3 const& fontColor, GLenum format)
        : GUI(tag, texturePath, format, format) {

    model->vertices.emplace_back(-1.f, 1.f, 0);
    model->vertices.emplace_back(1.f, 1.f, 0);
    model->vertices.emplace_back(1.f, -1.f, 0);

    model->vertices.emplace_back(1.f, -1.f, 0);
    model->vertices.emplace_back(-1.f, -1.f, 0);
    model->vertices.emplace_back(-1.f, 1.f, 0);

    model->uvs.emplace_back(0, 0);
    model->uvs.emplace_back(1, 0);
    model->uvs.emplace_back(1, 1);

    model->uvs.emplace_back(1, 1);
    model->uvs.emplace_back(0, 1);
    model->uvs.emplace_back(0, 0);

    set_anchor(position);
    set_dimension(dimension);
    update_dynamicData(position, dimension);

    guiRender.setData(this);

    Dimension dim = Text::preview_text(0, fontSize, text);
    Dimension d = (dimension - dim) / 2.f;
    d.y += dim.y;
    auto textBlock = new TextBlock("", text, fontSize, fontColor, position + glm::vec2(1.f, -1.f) * d);
    children.push_back(textBlock);
}

Button::~Button() {}

void Button::render() {
    if ( isVisible() ) {
        guiRender(dynamicData);
        GUI::render();
    }
}