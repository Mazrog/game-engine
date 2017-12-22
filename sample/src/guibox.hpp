//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUIBOX_HPP
#define ENGINE_GUIBOX_HPP

#include <gui/gui.hpp>
#include <gui/text.hpp>
#include "guiRender.hpp"
#include "textRender.hpp"

class Guibox : public GUI {
public:
    Guibox(std::string const& tag, const char * texturePath,
           GLenum format = GL_RGB, glm::vec2 position = glm::vec2(-1.f, 1.f),
           glm::vec2 scale = glm::vec2(1.f));
    ~Guibox();

    void render() override {
        if( isVisible() ) {
            guiRender(dynamicData);
            textRender(dynamicData, guiData);
        }
    }

private:
    GuiRender   guiRender;
    TextRender  textRender;
};


#endif //ENGINE_GUI_HPP
