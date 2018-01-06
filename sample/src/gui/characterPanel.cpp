//
// Created by mazrog on 28/12/17.
//

#include <gui/elements/table.hpp>
#include "characterPanel.hpp"


CharacterPanel::CharacterPanel(SGL_Node * character) :
        Guibox("characterPanel", L"Personnage", "sample/img/black.png",
               glm::vec2(-1.f, .55f), glm::vec2(.7f, 1.2f)), character(character) {

    auto * equipment = new Guibox("equip", L"", "sample/img/height_map.png", glm::vec2(-1.f, 1.f), glm::vec2(.7f, .9f));
    add(equipment);

    auto * caracs = new Table("caracs", "Caractéristiques", 5, 4, nullptr, glm::vec2(-1.f, -.2f), glm::vec2(.7f, 1.2f));
    caracs->add_cell(0, new TextBlock("", L"Force"));
    caracs->add_cell(0, new TextBlock("", L" : 12"));
    caracs->add_cell(0, new TextBlock("", L"Dextérité"));
    caracs->add_cell(0, new TextBlock("", L" : 21"));

    caracs->add_cell(1, new TextBlock("", L"Intelligence"));
    caracs->add_cell(1, new TextBlock("", L" : 11"));
    caracs->add_cell(1, new TextBlock("", L"Endurance"));
    caracs->add_cell(1, new TextBlock("", L" : 15"));

    add(caracs);
}

CharacterPanel::~CharacterPanel() {}

void CharacterPanel::render() {
    Guibox::render();
}

void CharacterPanel::build_guiData() {}