//
// Created by mazrog on 26/12/17.
//

#include "gui/elements/table.hpp"

Table::Table(std::string const &tag, std::string const& title, unsigned rows, unsigned cols,
             const char *texturePath, glm::vec2 position, glm::vec2 dimension, GLenum format) :
        GUI(tag, texturePath, format, format) {
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


    max_col = cols;
    grid.resize(rows);

    set_anchor(position);
    set_dimension(dimension);
    update_dynamicData();
    vert_flow += guiData.add_element("title", str_to_wstr(title)).y;

    col_sizes.assign(max_col, guiData.dimension.x / (float) max_col);

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

void Table::col_config(unsigned col_number, float size) {
    if ( col_number < max_col ) {
        float tmp = ( guiData.dimension.x - size ) / (float) ( max_col - 1 );
        col_sizes.assign(max_col, tmp);
        col_sizes.at(col_number) = size;
    }
}

void Table::add_cell(unsigned row_number, GUI *element) {
    if ( row_number < grid.size() ) {
        element->set_anchor(guiData.anchor);
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

GUI* Table::at(unsigned row, unsigned col) {
    return grid.at(row).at(col);
}

void Table::render() {
    if( isVisible() ) {
        /* Rendering table */
        if ( hasTexture() ) {
            guiRender(dynamicData);
        }
        textRender(dynamicData, guiData);

        Point point = guiData.anchor;
        float max_height;
        unsigned indice;
        /* Rendering table cells */
        for( auto & row : grid ) {
            max_height = 0.f;
            indice = 0;
            for( auto & cell : row ) {
                cell->set_anchor(point);
                cell->render();
                point.x += col_sizes.at(indice++);
                max_height = ( cell->get_content_dimension().y > max_height ) ? cell->get_content_dimension().y : max_height;
            }
            point.x = guiData.anchor.x;
            point.y -= max_height;
        }
    }
}