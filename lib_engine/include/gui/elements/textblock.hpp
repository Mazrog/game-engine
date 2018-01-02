//
// Created by mazrog on 26/12/17.
//

#ifndef ENGINE_TEXTBLOCK_HPP
#define ENGINE_TEXTBLOCK_HPP

#include "gui/guiRender.hpp"
#include "gui/textRender.hpp"

class TextBlock : public GUI {
public:
    TextBlock(std::string const& tag, std::string const& text, unsigned fontSize = 20, glm::vec3 fontColor = glm::vec3(1.f),
            glm::vec2 position = glm::vec2(-1.f, 1.f),
            glm::vec2 dimension = glm::vec2(1.f));

    TextBlock(std::string const& tag, std::wstring const& text, unsigned fontSize = 20, glm::vec3 fontColor = glm::vec3(1.f),
              glm::vec2 position = glm::vec2(-1.f, 1.f),
              glm::vec2 dimension = glm::vec2(1.f));

    ~TextBlock();

    void render() override {
        if( isVisible() ) {
            textRender(dynamicData, guiData);
        }
    }

private:
    TextRender  textRender;
};


#endif //ENGINE_TEXTBLOCK_HPP
