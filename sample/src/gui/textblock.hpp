//
// Created by mazrog on 26/12/17.
//

#ifndef ENGINE_TEXTBLOCK_HPP
#define ENGINE_TEXTBLOCK_HPP

#include "guiRender.hpp"
#include "textRender.hpp"
#include <gui/gui.hpp>

class TextBlock : public GUI {
public:
    TextBlock(std::string const& tag, std::string const& text,
            glm::vec2 position = glm::vec2(-1.f, 1.f),
            glm::vec2 dimension = glm::vec2(1.f));

    TextBlock(std::string const& tag, std::wstring const& text,
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
