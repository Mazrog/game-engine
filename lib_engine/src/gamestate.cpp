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
        onInit(init), logic(logic), onExit(exit),
        sgl(std::make_shared<SGL>()) {
//    std::cout << "make game state" << std::endl;
}

GameState::~GameState() {}

GameState::GameState(GameState && gs) :
        onInit(std::move(gs.onInit)), logic(std::move(gs.logic)),
        onExit(std::move(gs.onExit)), sgl(std::move(gs.sgl)) {
//    std::cout << "move game state" << std::endl;
}

void GameState::init(GameState * self) { onInit(self); }

void GameState::exit(GameState * self) { onExit(self); }

void GameState::main(GameState * self) {
    int ns = logic(self);

    if(ns > -1) {
        exit();
        Engine::get_controller().set_state(static_cast<unsigned int>(ns));
    }
}

void GameState::main() { main(this); }

void GameState::init() { init(this); }

void GameState::exit() { exit(this); }

void GameState::bind(SG_NODE_TYPE type, const char * name, SGL_Node *node) {
    sgl->bind(type, name, node);
}

SGL_Node * GameState::get(const char *name) {
    return sgl->graph.at(name);
}

Camera * GameState::get_as_camera(const char *name) {
    return dynamic_cast<Camera *>(sgl->graph.at(name));
}