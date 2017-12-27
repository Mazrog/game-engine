//
// Created by mazrog on 26/12/17.
//

#include "table.hpp"

Table::Table(std::string const &tag, std::string const& title, unsigned rows, unsigned cols,
             const char *texturePath, glm::vec2 position, glm::vec2 dimension, GLenum format) :
        GUI(tag, texturePath, format, format) {
    max_col = cols;
    grid.resize(rows);

    model->vertices.emplace_back(-1.f, 1.f, 0);
    model->vertices.emplace_back(1.f, 1.f, 0);
    model->vertices.emplace_back(1.f, -1.f, 0);

    model->vertices.emplace_back(1.f, -1.f, 0);
    model->vertices.emplace_back(-1.f, -1.f, 0);
    model->vertices.emplace_back(-1.f, 1.f, 0);

    model->uvs.emplace_back(0, 0);
    model->uvs.emplace_back(1, 0);
    model->uvs.emplace_back(1, 1);

    model->uvs.emplace_back(1, 1);
    model->uvs.emplace_back(0, 1);
    model->uvs.emplace_back(0, 0);

    /* Dimension to scale */
    dynamicData.scale = glm::vec3(dimension / 2.f, 0);
    /* Setting the translate to the upper left corner */
    dynamicData.position = glm::vec3(position, 0.f) - glm::vec3(-1.f, 1.f, 0.f) * dynamicData.scale;

    dynamicData.update();

    set_anchor(position);
    guiData.guiContent.at("title")->text.assign(title.begin(), title.end());

    guiRender.setData(this);
    textRender.setData(this);
}

Table::~Table() {
    for( auto & row : grid ) {
        for( auto & cell : row ) {
            delete cell;
        }
    }
}

void Table::add_row() {
    grid.emplace_back();
}

void Table::add_cell(unsigned row_number, GUI *element) {
    if ( row_number < grid.size() ) {
        grid.at(row_number).push_back(element);
        unsigned size = grid.at(row_number).size();
        if ( size > max_col ) { max_col = size; }
    }
}

void Table::spread_visibility() {
    GUI::spread_visibility();
    for( auto const& row : grid ) {
        for( auto const& cell : row ) {
            cell->set_visibility(visible);
        }
    }
}

void Table::render() {
    if( isVisible() ) {
        /* Rendering table */
        guiRender(dynamicData);
        textRender(dynamicData, guiData);

        Point point = guiData.anchor;
        float max_height;
        /* Rendering table cells */
        for( auto & row : grid ) {
            max_height = 0.f;
            for( auto & cell : row ) {
                cell->set_anchor(point);
                cell->render();
                point.x += cell->get_dimension().x;
                max_height = ( cell->get_dimension().y > max_height ) ? cell->get_dimension().y : max_height;
            }
            point.y -= max_height;
            point.x = guiData.anchor.x;
        }
    }
}