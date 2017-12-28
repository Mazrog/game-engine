//
// Created by mazrog on 21/12/17.
//

#include "gui/elements/guibox.hpp"

Guibox::Guibox(std::string const &tag, std::string const& title, const char * texturePath,
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

    /* Dimension to scale */
    dynamicData.scale = glm::vec3(dimension / 2.f, 0);
    /* Setting the translate to the upper left corner */
    dynamicData.position = glm::vec3(position, 0.f) - glm::vec3(-1.f, 1.f, 0.f) * dynamicData.scale;

    dynamicData.update();

    guiData.anchor = position;
    guiData.guiContent.at("title")->text.assign(title.begin(), title.end());

    guiRender.setData(this);
    textRender.setData(this);
}

Guibox::~Guibox() {}

void Guibox::set_title(std::wstring const &title) {
    guiData.guiContent.at("title")->text = title;
}