//
// Created by mazrog on 11/11/17.
//

#include "engine.hpp"
#include "gamestate.hpp"
#include "rendering/camera.hpp"

/* Classe State */
GameState::GameState(
        std::function<int(GameState * self)> const&    logic,
        std::function<void(GameState * self)> const&   init,
        std::function<void(GameState * self)>  const&  exit) :
        onInit(init), logic(logic), onExit(exit),
        sgl(new SGL()), models(), guiManager(new GuiManager),
        hasBeenInit(false), saved(false){}

GameState::~GameState() {
    delete sgl;
    delete guiManager;
    for ( auto & model : models ) {
        delete model.second;
    }
}

GameState::GameState(GameState && gs) :
        onInit(std::move(gs.onInit)), logic(std::move(gs.logic)),
        onExit(std::move(gs.onExit)), sgl(gs.sgl) {}

void GameState::init(GameState * self) {
    if(!hasBeenInit) {
        onInit(self);
        hasBeenInit = true;
    }
    saved = false;
}

void GameState::exit(GameState * self){
    if(!saved) {
        onExit(self);
        hasBeenInit = false;
        clear();
    }
}

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

void GameState::save_state() {
    saved = true;
}

void GameState::clear() {
    sgl->clear();
    models.clear();
    guiManager->clear();
}

void GameState::bind(SG_NODE_TYPE type, const char *name, SGL_Node *node, unsigned renderGroupID) {
    sgl->bind(type, name, node, renderGroupID);
}

void GameState::load_model(const char *tag, const char *file) {
    auto * model = new Model(file);
    auto it = models.find(tag);

    if( it == models.end() ) { models[tag] = model; }
    else { std::cerr << "Double model insertion for tag : " << tag << std::endl; }
}

void GameState::add_gui(GUI *gui) {
    guiManager->add(gui);
}

void GameState::gui_events() {
    guiManager->spread_events();
}

void GameState::set_guiManager(GuiManager *new_guiManager) {
    delete guiManager;
    guiManager = new_guiManager;
}

SGL_Node * GameState::get(const char *name) {
    return sgl->graph.at(name);
}

Camera * GameState::get_camera() {
    return sgl->camera;
}