//
// Created by mazrog on 11/11/17.
//

#include <engine.hpp>
#include "gamestate.hpp"

/* Classe State */
GameState::GameState(
        std::function<int()> const&    logic,
        std::function<void()> const&   init,
        std::function<void()>  const&  exit) :
        onInit(init), logic(logic), onExit(exit),
        sgl(nullptr) {}

GameState::~GameState() {
    delete sgl;
}

void GameState::init() { onInit(); }

void GameState::exit() { onExit(); }

void GameState::main() {
    int ns = logic();

    if(ns > -1) {
        onExit();
        Engine::get_controller().set_state(static_cast<unsigned int>(ns));
    }
}