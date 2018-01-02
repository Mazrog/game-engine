//
// Created by mazrog on 26/12/17.
//

#include "gui/elements/textblock.hpp"

TextBlock::TextBlock(std::string const &tag, std::string const& text, unsigned fontSize, glm::vec3 fontColor, glm::vec2 position, glm::vec2 dimension) :
        TextBlock(tag, str_to_wstr(text), fontSize, fontColor, position, dimension) {}

TextBlock::TextBlock(std::string const &tag, std::wstring const &text, unsigned fontSize, glm::vec3 fontColor, glm::vec2 position, glm::vec2 dimension) : GUI(tag, nullptr) {
    guiData.add_element("content", text, fontSize, fontColor);

    dynamicData.scale = glm::vec3(dimension / 2.f, 0);
    dynamicData.position = glm::vec3(position, 0.f) - glm::vec3(-1.f, 1.f, 1.f) * dynamicData.scale;

    dynamicData.update();

    guiData.anchor = position;

    textRender.setData(this);
}

TextBlock::~TextBlock() {}