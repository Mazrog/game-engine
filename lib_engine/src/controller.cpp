//
// Created by mazrog on 10/11/17.
//

#include <SDL2/SDL.h>

#include "engine.hpp"
#include "controller.hpp"

/* ######################################################## */
/* Dequeuing the events saved in the event Context */
int poll_event(SDL_Event *event) {
    std::queue<SDL_Event> & queue = Engine::get_controller().eventContext.events;

    if(queue.empty()){
        return 0;
    } else {
        *event = queue.front();
        queue.pop();
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
}

void Controller::start() {
    set_state(0);
}

void Controller::load_sgl_from_state() {
    if(states.size() > current_state){
        sgl = states.at(current_state)->get_sgl();
        build_sgv_from_sgl();
    } else {
        std::cerr << "No current state to get the SGL from, please set one." << std::endl;
    }
}

void Controller::build_sgv_from_sgl() {
    SGV * sgv = new SGV();

    for(auto& it : sgl->rendering_order){
        sgv->nodes.push_back(it);
    }

    /* Convert phase */
    /* Updating the sgv */
    Engine::engine.data.sgv = sgv;
}

/* ############################################################################ */
void Controller::set_state(unsigned int next_state) {
    if(states.size() > next_state) {
        current_state = next_state;
        states.at(current_state)->init();

        load_sgl_from_state();
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
