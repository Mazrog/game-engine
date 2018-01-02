//
// Created by mazrog on 21/12/17.
//

#include <iostream>

#include "gui/gui.hpp"

/* ------------------------------------------------- */
GUI::GUI(std::string const& tag, const char * texturePath, GLenum internalFormat, GLenum format) :
        tag(tag), visible(false), vert_flow(0), model(new Model()),
        textureFormat(texturePath, internalFormat, format) {}

GUI::~GUI() {
    delete model;
}

void GUI::debug() const {
    std::cout << "------------------ DEBUG ------------------" << std::endl;
    std::cout << "TAG : " << tag << "\t\t Anchor : " << guiData.anchor.x << " # " << guiData.anchor.y << std::endl;
    std::cout << "Position : " << dynamicData.position.x << " # " << dynamicData.position.y << std::endl;

    std::cout << std::endl;
}

void GUI::add(GUI *child) {
    Point anchor = guiData.anchor;
    anchor.y -= vert_flow;
    child->set_anchor(anchor);
    child->update_dynamicData();
    children.push_back(child);

    vert_flow += child->get_dimension().y;
}

void GUI::add(std::string const &, std::wstring const &, unsigned int , const glm::vec3 &) {}

void GUI::update_dynamicData() {
    update_dynamicData(get_anchor(), get_dimension());
}

void GUI::update_dynamicData(glm::vec2 const &position, glm::vec2 const &dimension) {
    /* Dimension to scale */
    dynamicData.scale = glm::vec3(dimension / 2.f, 0);
    /* Setting the translate to the upper left corner */
    dynamicData.position = glm::vec3(position, 0.f) - glm::vec3(-1.f, 1.f, 0.f) * dynamicData.scale;

    dynamicData.update();
}

void GUI::spread_visibility() {
    for(auto const& gui : children) {
        gui->set_visibility(visible);
        gui->spread_visibility();
    }
}

void GUI::show() {
    if( !visible ) {
        visible = true;
        spread_visibility();
    }
}

void GUI::hide() {
    if( visible ) {
        visible = false;
        spread_visibility();
    }
}

void GUI::toggle() {
    visible ? hide() : show();
}

void GUI::build_guiData() {}

void GUI::render() {
    for(auto const& gui : children) {
        gui->render();
    }
}