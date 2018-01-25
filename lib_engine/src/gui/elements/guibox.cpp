//
// Created by mazrog on 21/12/17.
//

#include "gui/elements/guibox.hpp"

Guibox::Guibox(std::string const &tag, std::wstring const& title, const char * texturePath,
               glm::vec2 const& position, glm::vec2 const& dimension, GLenum format) :
        GUI(tag, texturePath, format, format), guiRender() {

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

    set_anchor(position);
    set_dimension(dimension);
    update_dynamicData(position, dimension);
    if( !title.empty() ) {
        vert_flow += 1.5 * guiData.add_element("title", title).y;
        vert_flow += 0.01f;
    }


    guiRender.setData(this);
    textRender.setData(this);
}

Guibox::~Guibox() {}

void Guibox::set_title(std::wstring const &title) {
    guiData.guiContent.at("title")->text = title;
}