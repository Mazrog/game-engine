//
// Created by mazrog on 28/12/17.
//

#include "characterPanel.hpp"


CharacterPanel::CharacterPanel(SGL_Node * character) :
        Guibox("characterPanel", "Personnage", "sample/img/crate.jpg",
               glm::vec2(-.999f, .52f), glm::vec2(.55f, 1.1f), GL_RGB), character(character) {}

CharacterPanel::~CharacterPanel() {}

void CharacterPanel::build_guiData() {}