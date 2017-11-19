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
    /* Initialisation of the event Context */
    eventContext = Controller::EventContext{
            SDL_GetKeyboardState(nullptr),
            std::queue<SDL_Event>()
    };
}

/* Loading the State at pos 0 if exists */
void Controller::start() { set_state(0); }


/* Getting the Logic Scenegraph from the current state */
void Controller::load_sgl_from_state() {
    /* Testing if the wanted state is correct */
    if(states.size() > current_state){
        sgl = states.at(current_state)->get_sgl();

        /* Update the Engine Visual Scenegraph with the new Logical graph */
        build_sgv_from_sgl();
    } else { std::cerr << "No current state to get the SGL from, please set one." << std::endl; }
}

void Controller::build_sgv_from_sgl() {
    std::unique_ptr<SGV> sgv = std::make_unique<SGV>(sgl);

    /* Convert phase */
    /* Updating the sgv */
    Engine::engine.data.sgv = std::move(sgv);
}

/* ############################################################################ */

void Controller::set_state(unsigned int next_state) {
    /* Checking the argument relevance */
    if(states.size() > next_state) {
        /* Changing the current state */
        current_state = next_state;
        /* Initialisation of the new current state */
        states.at(current_state)->init();

        /* Getting the new Logic Scenegraph */
        load_sgl_from_state();
    } else {
        std::cerr << "Invalid state id : " << next_state << std::endl;
        /* If invalid id, quit the engine */
        end();
    }
}

/* Root main function handling events before the current state */
void Controller::control() {
    auto keyboard  = eventContext.keyboard;
    SDL_Event ev;

    while(SDL_PollEvent(&ev)){
        /* Filling up the queue for later use */
        eventContext.events.push(ev);

        switch (ev.type){
            /* Quit button on the window */
            case SDL_QUIT:
                /* Leaving the engine */
                end();
            default:;
        }
    }

    /* Dev purpose -> escape key closes the engine */
    if(keyboard[SDL_SCANCODE_ESCAPE]) {
        std::cout << "exit" << std::endl;
        end();
    }

    /* If the engine is still running, starting the main loop of the state */
    if(Engine::engine.data.running) {
        states.at(current_state)->main();
    }
}

/* Ending of the engine */
void Controller::end() {
    /* Ending the current state */
    states.at(current_state)->exit();
    /* Un referencing the Logic Scenegraph */
    sgl = nullptr;
    /* Telling the engine to stop */
    Engine::engine.data.running = false;
}
