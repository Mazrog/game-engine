//
// Created by mazrog on 26/12/17.
//

#include "gui/elements/textblock.hpp"

TextBlock::TextBlock(std::string const &tag, std::string const& text, unsigned fontSize, glm::vec3 fontColor, glm::vec2 position, glm::vec2 dimension) :
        TextBlock(tag, str_to_wstr(text), fontSize, fontColor, position, dimension) {}

TextBlock::TextBlock(std::string const &tag, std::wstring const &text, unsigned fontSize,
                     glm::vec3 fontColor, glm::vec2 position, glm::vec2 dimension) : GUI(tag, nullptr) {
    guiData.add_element("content", text, fontSize, fontColor);

    guiData.anchor = position;

    textRender.setData(this);
}

TextBlock::~TextBlock() {}