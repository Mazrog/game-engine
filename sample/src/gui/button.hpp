//
// Created by mazrog on 06/01/18.
//

#ifndef ENGINE_BUTTON_HPP
#define ENGINE_BUTTON_HPP


#include <gui/gui.hpp>
#include <gui/elements/textblock.hpp>

class Button : public GUI {
public:
    Button(std::string const& tag, std::wstring const& text,
           const char * texturePath,
           glm::vec2 const& position,
           glm::vec2 const& dimension,
           unsigned fontSize = 20,
           glm::vec3 const& fontColor = glm::vec3(1.f),
           GLenum format = GL_RGB);
    ~Button();

    void render() override;

private:
    GuiRender   guiRender;
};


#endif //ENGINE_BUTTON_HPP
