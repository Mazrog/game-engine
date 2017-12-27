//
// Created by mazrog on 26/12/17.
//

#ifndef ENGINE_TABLE_HPP
#define ENGINE_TABLE_HPP

#include "guiRender.hpp"
#include "textRender.hpp"

using Grid = std::vector<std::vector<GUI *>>;

class Table : public GUI {
public:
    Table(std::string const& tag, std::string const& title = "", unsigned rows = 0, unsigned cols = 0, const char * texturePath = nullptr,
            glm::vec2 position = glm::vec2(-1.f, 1.f),
            glm::vec2 dimension = glm::vec2(1.f),
            GLenum format = GL_RGB);

    ~Table();

    void add_row();
    void add_cell(unsigned row_number, GUI * element);

    void spread_visibility();

    void render() override;

private:
    /* Rendering stuff */
    GuiRender   guiRender;
    TextRender  textRender;

    /* -- */
    unsigned    max_col;
    Grid        grid;
};


#endif //ENGINE_TABLE_HPP
