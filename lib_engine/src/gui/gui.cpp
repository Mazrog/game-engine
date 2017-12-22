//
// Created by mazrog on 21/12/17.
//

#include <iostream>

#include "gui/gui.hpp"

GUI::GUI(std::string const& tag, const char * texturePath, GLenum internalFormat, GLenum format) :
        tag(tag), visible(false), model(new Model()),
        textureFormat(texturePath, internalFormat, format) {
    guiData.text.assign(tag.begin(), tag.end());
}

GUI::~GUI() {
    delete model;
}

void GUI::show() {
    if( !visible ) {
//        std::cout << "Affichage : " << tag << std::endl;
        visible = true;
    }
}

void GUI::hide() {
    if( visible ) {
//        std::cout << "Cache : " << tag << std::endl;
        visible = false;
    }
}

void GUI::toggle() {
    visible ? hide() : show();
}

void GUI::render() {}