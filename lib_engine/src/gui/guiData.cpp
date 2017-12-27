//
// Created by mazrog on 26/12/17.
//

#include "gui/guiData.hpp"

TextElement::TextElement(std::wstring const &text, const glm::vec3 &font_color, unsigned font_size) :
        text(text), font_color(font_color), font_size(font_size) {}

/* ------------------------------------------------- */
GuiData::GuiData() {}

GuiData::~GuiData() {
    for(auto & pair : guiContent) {
        delete pair.second;
    }
}

void GuiData::add_element(const char *tag, std::wstring const& text, unsigned font_size, glm::vec3 const& font_color) {
    auto * elem = new TextElement(text, font_color, font_size);
    guiContent.insert({tag, elem});
}

std::wstring str_to_wstr(std::string const& text) {
    std::wstring wstring(text.begin(), text.end());
    return wstring;
}

void str_to_wstrIP(std::string const& text, std::wstring & wstring) {
    wstring.assign(text.begin(), text.end());
}