//
// Created by mazrog on 21/12/17.
//

#include <iostream>
#include "utils.hpp"
#include "gui/guiManager.hpp"

#include "events/keyboard.hpp"

GuiManager::GuiManager() {}

GuiManager::~GuiManager() {
    clear();
}

void GuiManager::add(GUI *gui) {
    if ( guis.find(gui->tag) == guis.end() ) {
        guis[gui->tag] = gui;
    } else {
        std::cerr << "Warning : You tried to insert two GUI element with the same tag [" << gui->tag << " ]." << std::endl;
    }
}

void GuiManager::clear() {
    for(auto & pair : guis) {
        delete pair.second;
    }
    guis.clear();
}