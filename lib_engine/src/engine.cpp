//
// Created by mazrog on 10/11/17.
//

#include <iostream>

#include "engine.hpp"

Engine Engine::engine;

Engine::Engine() : start_loop(-1) {
    data = Data{
        nullptr,    // Window *
        nullptr,    // GL Context
        nullptr,    // SGV
        true,       // Engine is running
        60,         // Disp  loop frequency
    };
}

void Engine::Data::clear() {
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    delete sgv;
}

void Engine::init() {
    engine.display.init(engine.data.win, engine.data.ctx);
    engine.controller.init();
}

void Engine::start() {
    engine.controller.start();

    while(engine.data.running){
        /* Display */
        engine.display.cls();
        engine.display.render_sgv(engine.data.sgv);
        engine.display.frame();

        /* Controller */
        engine.controller.control();
        delay();
    }

    engine.onQuit();
}

void Engine::delay() {
    /* Calcul true duration */
    unsigned int dt = static_cast<unsigned int>(1000 / Engine::engine.data.freq_disp);
    SDL_Delay(dt);
}

void Engine::onQuit() {
    data.clear();
}