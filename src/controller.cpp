//
// Created by mazrog on 10/11/17.
//

#include <SDL2/SDL.h>

#include "engine.hpp"
#include "controller.hpp"

/* ######################################################## */
/* Dequeuing the events saved in the event Context */
int poll_event(SDL_Event *event) {
    if(Engine::get_controller().eventContext.events.empty()){
        return 0;
    } else {
        *event = Engine::get_controller().eventContext.events.front();
        Engine::get_controller().eventContext.events.pop();
        return 1;
    }
}

/* ######################################################## */
/* Begin of controller class */

Controller::Controller() : sgl(nullptr) {}

void Controller::init() {
    eventContext = Controller::EventContext{
            SDL_GetKeyboardState(nullptr),
            std::queue<SDL_Event>()
    };

    current_state = 0;
}

void Controller::start() {
    states.at(current_state)->init();
}

void Controller::load_sgl_from_state() {
    if(states.size() > current_state){
        sgl = states.at(current_state)->get_sgl();
    } else {
        std::cerr << "No current state to get the SGL from, please set one." << std::endl;
    }
}

void Controller::build_sgv_from_sgl() {
    SGV * sgv = nullptr;

    /* Convert phase */
    /* Updating the sgv */
    Engine::engine.data.sgv = sgv;
}

/* ############################################################################ */
void Controller::set_state(unsigned int next_state) {
    if(states.size() > next_state) {
        current_state = next_state;
//        states.at(current_state)->init();

        /* Getting the sgl from the current state if updated */
//        load_sgl_from_state();
    } else {
        std::cerr << "Invalid state id : " << next_state << std::endl;
        end();
    }
}

void Controller::control() {
    auto keyboard  = eventContext.keyboard;
    SDL_Event ev;

    while(SDL_PollEvent(&ev)){
        eventContext.events.push(ev);

        switch (ev.type){
            case SDL_QUIT:
                end();
            default:;
        }
    }

    if(keyboard[SDL_SCANCODE_ESCAPE]) {
        std::cout << "exit" << std::endl;
        end();
    }

    if(Engine::engine.data.running) {
        states.at(current_state)->main();
    }
}

void Controller::end() {
    sgl = nullptr;
    Engine::engine.data.running = false;
}

/* Classe State */
Controller::State::State(
                         std::function<int()> const&    logic,
                         std::function<void()> const&   init,
                         std::function<void()>  const&  exit) :
        onInit(init), logic(logic), onExit(exit),
        sgl(nullptr) {}

void Controller::State::main() {
    int ns = logic();
//    std::cout << "return " << ns << std::endl;

    if(ns > -1) {
        onExit();
        Engine::engine.controller.set_state(static_cast<unsigned int>(ns));
    }
}
