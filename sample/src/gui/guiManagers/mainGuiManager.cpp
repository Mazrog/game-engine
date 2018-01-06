//
// Created by mazrog on 05/01/18.
//

#include "mainGuiManager.hpp"

MainGuiManager::MainGuiManager(GameState * state, GuiEvents events)
        : state(state), events(std::move(events)) {}

MainGuiManager::~MainGuiManager() = default;

void MainGuiManager::spread_events() {
    events(this, state);
}