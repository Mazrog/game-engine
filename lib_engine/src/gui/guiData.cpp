//
// Created by mazrog on 26/12/17.
//

#include "gui/guiData.hpp"
#include "gui/text.hpp"

TextElement::TextElement(std::wstring const &text, unsigned font_size, const glm::vec3 &font_color) :
        text(text), font_color(font_color), font_size(font_size) {}

/* ------------------------------------------------- */
GuiData::GuiData() {}

GuiData::~GuiData() {
    for(auto & pair : guiContent) {
        delete pair.second;
    }
}

Dimension GuiData::add_element(const char *tag, std::wstring const& text, unsigned font_size, glm::vec3 const& font_color) {
    auto * elem = new TextElement(text, font_size, font_color);
    guiContent.insert({tag, elem});

    return Text::preview_text(0, font_size, L"A");
}

std::wstring str_to_wstr(std::string const& text) {
    std::wstring wstring(text.begin(), text.end());
    return wstring;
}

std::string wstr_to_str(std::wstring const& text) {
    std::string string(text.begin(), text.end());
    return string;
}

void str_to_wstrIP(std::string const& text, std::wstring & wstring) {
    wstring.assign(text.begin(), text.end());
}