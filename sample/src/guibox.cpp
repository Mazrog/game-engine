//
// Created by mazrog on 21/12/17.
//

#include "guibox.hpp"

Guibox::Guibox(std::string const &tag, const char * texturePath, GLenum format,
               glm::vec2 position, glm::vec2 scale) :
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


    dynamicData.scale = glm::vec3(scale, 0);

    dynamicData.position = glm::vec3(position - glm::vec2(-1.f, 1.f) * scale, 0);
    dynamicData.update();

    guiRender.setData(this);
    textRender.setData(this);
}

Guibox::~Guibox() {}

