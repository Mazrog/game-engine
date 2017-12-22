//
// Created by mazrog on 21/12/17.
//

#include <iostream>
#include "utils.hpp"
#include "gui/guiManager.hpp"

#include "events/keyboard.hpp"

GuiManager::GuiManager() {}

GuiManager::~GuiManager() {
    for(auto & pair : guis) {
        delete pair.second;
    }
}

void GuiManager::add(GUI *gui) {
    if ( guis.find(gui->tag) == guis.end() ) {
        guis[gui->tag] = gui;
    } else {
        std::cerr << "Warning : You tried to insert two GUI element with the same tag [" << gui->tag << " ]." << std::endl;
    }
}

void GuiManager::spread_events() {
    Keyboard keyboard = Keyboard::keyboard;

    int key_press = keyboard.action == GLFW_PRESS || keyboard.action == GLFW_REPEAT;

    if( keyboard.key == GLFW_KEY_B && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            guis.at("inventory")->hide();
        } else {
            guis.at("inventory")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_C && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            guis.at("charInfo")->hide();
        } else {
            guis.at("charInfo")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_H && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            guis.at("help")->hide();
        } else {
            guis.at("help")->show();
        }
    }
}