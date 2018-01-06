//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUIBOX_HPP
#define ENGINE_GUIBOX_HPP

#include "gui/guiRender.hpp"
#include "gui/textRender.hpp"

class Guibox : public GUI {
public:
    Guibox(std::string const& tag, std::wstring const& title,
           const char * texturePath = nullptr,
           glm::vec2 const& position = glm::vec2(-1.f, 1.f),
           glm::vec2 const& dimension = glm::vec2(2.f),
           GLenum format = GL_RGB);

    ~Guibox();

    void render() override {
        if( isVisible() ) {
            guiRender(dynamicData);
            textRender(dynamicData, guiData);
            GUI::render();
        }
    }

    void set_title(std::wstring const& title);

private:
    GuiRender   guiRender;
    TextRender  textRender;
};


#endif //ENGINE_GUI_HPP
