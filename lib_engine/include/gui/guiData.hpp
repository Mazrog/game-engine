//
// Created by mazrog on 26/12/17.
//

#ifndef ENGINE_GUIDATA_HPP
#define ENGINE_GUIDATA_HPP

#include <string>
#include <map>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

using Point = glm::vec2;
using Dimension = glm::vec2;

struct TextElement {
    std::wstring    text;
    glm::vec3       font_color;
    unsigned        font_size;

    TextElement(std::wstring const& text, glm::vec3 const& font_color = glm::vec3(1.f), unsigned font_size = 24);
};

using GuiContent = std::map<std::string, TextElement *>;

class GuiData {
public:
    GuiData();
    ~GuiData();

    void add_element(const char * tag, std::wstring const& text, unsigned font_size = 24, glm::vec3 const& font_color = glm::vec3(1.f));

    Dimension   dimension;
    Point       anchor;

public:
    GuiContent      guiContent;

};

std::wstring str_to_wstr(std::string const& text);

void str_to_wstrIP(std::string const& text, std::wstring & wstring);

#endif //ENGINE_GUIDATA_HPP
