//
// Created by mazrog on 21/12/17.
//

#include "guibox.hpp"

Guibox::Guibox(std::string const &tag) : GUI(tag), guiRender() {

    float val = 0.f;

    model->vertices.emplace_back(-.8f, .8f, val);
    model->vertices.emplace_back(0.f, .8f, val);
    model->vertices.emplace_back(0.f, -.8f, val);
    
    model->vertices.emplace_back(0.f, -.8f, val);
    model->vertices.emplace_back(-.8f, -.8f, val);
    model->vertices.emplace_back(-.8f, .8f, val);
    
    model->uvs.emplace_back(0, 0);
    model->uvs.emplace_back(1, 0);
    model->uvs.emplace_back(1, 1);
    
    model->uvs.emplace_back(1, 1);
    model->uvs.emplace_back(0, 1);
    model->uvs.emplace_back(0, 0);


    dynamicData.update();

    guiRender.setData(this);
}

Guibox::~Guibox() {}

