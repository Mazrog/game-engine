//
// Created by mazrog on 21/12/17.
//

#include <iostream>

#include "gui/gui.hpp"

/* ------------------------------------------------- */
GUI::GUI(std::string const& tag, const char * texturePath, GLenum internalFormat, GLenum format) :
        tag(tag), visible(false), model(new Model()),
        textureFormat(texturePath, internalFormat, format) {
    guiData.add_element("title", str_to_wstr(tag));
}

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
    child->set_anchor(guiData.anchor);
    children.push_back(child);
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

void GUI::render() {
    for(auto const& gui : children) {
        gui->render();
    }
}