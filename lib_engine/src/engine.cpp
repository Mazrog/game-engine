//
// Created by mazrog on 10/11/17.
//

#include <iostream>
#include <chrono>
#include <thread>

#include "engine.hpp"

Engine Engine::engine;

Engine::Engine() {
    /* Initialisation of the Data structure */
    data = Data{
        nullptr,    // GLFW Window *
        nullptr,    // Visual Scenegraph
        true,       // Engine is running
        60,         // Display loop frequency
    };
}

void Engine::Data::clear() {
    glfwDestroyWindow(win);
    sgv = nullptr;
}

void Engine::init() {
    /* Initialisation of the display (window, context) */
    engine.display.init(engine.data.win);

    /* Controller init */
    engine.controller.init();
}

void Engine::start() {
    /* Starting the controller */
    engine.controller.start();

    /* Game MAIN loop */
    while(engine.data.running){
        /* ############### Controller logic ############### */
        engine.controller.control();


        /* ############### Display phase ############### */
        /* Clearing the screen */
        engine.display.cls();

        /* Rendering the current scene */
        engine.display.render_sgv(engine.data.sgv.get());

        /* Next frame */
        engine.display.frame();

        /* Delay to wait */
        delay();
    }
    /* END of MAIN LOOP */

    /* Releasing resources and leaving the engine */
    engine.onQuit();
}

void Engine::delay() {
    /* TODO : Calcul true duration */
    /* glfwGetTime(); */
    unsigned int dt = static_cast<unsigned int>(1000 / Engine::engine.data.freq_disp);

    std::this_thread::sleep_for(std::chrono::milliseconds(dt));
}

void Engine::onQuit() {
    /* Clearing resources */
    data.clear();
}