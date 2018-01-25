//
// Created by mazrog on 26/12/17.
//

#ifndef ENGINE_TABLE_HPP
#define ENGINE_TABLE_HPP

#include "gui/guiRender.hpp"
#include "gui/textRender.hpp"

using Grid = std::vector<std::vector<GUI *>>;

class Table : public GUI {
public:
    Table(std::string const& tag, std::wstring const& title = L"", unsigned rows = 0, unsigned cols = 0, const char * texturePath = nullptr,
            glm::vec2 position = glm::vec2(-1.f, 1.f),
            glm::vec2 dimension = glm::vec2(1.f),
            GLenum format = GL_RGB);

    ~Table();

    void add_row();
    void col_config(unsigned col_number, float size);
    void add_cell(unsigned row_number, GUI * element);

    void spread_visibility();

    void render() override;

    GUI * at(unsigned row, unsigned col);

private:
    /* Rendering stuff */
    GuiRender   guiRender;
    TextRender  textRender;

    /* -- */
    Grid        grid;
    unsigned    max_col;

    std::vector<float>  col_sizes;
};


#endif //ENGINE_TABLE_HPP
