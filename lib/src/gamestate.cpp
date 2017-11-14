//
// Created by mazrog on 11/11/17.
//

#include "engine.hpp"
#include "gamestate.hpp"

/* Classe State */
GameState::GameState(
        std::function<int(GameState * self)> const&    logic,
        std::function<void(GameState * self)> const&   init,
        std::function<void(GameState * self)>  const&  exit) :
        onInit(init), logic(logic), onExit(exit) {
    sgl = new SGL();
}

GameState::~GameState() {
    delete sgl;
}

void GameState::init(GameState * self) { onInit(self); }

void GameState::exit(GameState * self) { onExit(self); }

void GameState::main(GameState * self) {
    int ns = logic(self);

    if(ns > -1) {
        onExit(self);
        Engine::get_controller().set_state(static_cast<unsigned int>(ns));
    }
}

void GameState::main() { main(this); }

void GameState::init() { init(this); }

void GameState::bind(SG_NODE_TYPE type, const char * name, SGL_Node *node) {
    sgl->bind(type, name, node);
}