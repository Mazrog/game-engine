//
// Created by mazrog on 10/11/17.
//

#include "engine.hpp"
#include "controller.hpp"

/* ######################################################## */
/* Begin of controller class */

Controller::Controller() : sgl(nullptr) {}

Controller::~Controller() {
    for(auto & state : states) {
        state->exit();
        delete state;
    }
    states.clear();
}

void Controller::init() {
    /* Setting the events callback */
    GLFWwindow * win = Engine::engine.data.win;
    glfwSetKeyCallback(win, key_callback);
    glfwSetCursorPosCallback(win, cursor_position_callback);
    glfwSetMouseButtonCallback(win, mouse_button_callback);
    glfwSetScrollCallback(win, scroll_callback);

    glfwSetInputMode(win, GLFW_STICKY_MOUSE_BUTTONS, 1);

    states.clear();
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
    std::unique_ptr<SGV> sgv = std::make_unique<SGV>(sgl, states.at(current_state)->get_guiManager());

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

GameState* Controller::get_current_state() const {
    if( current_state < states.size() ) {
        return states.at(current_state);
    }
    return nullptr;
}

/* Root main function handling events before the current state */
void Controller::control() {
    /* Getting the events polled */
    glfwPollEvents();

    /* If the window should close (QUIT BUTTTON) */
    if(glfwWindowShouldClose(Engine::engine.data.win)) {
        /* Then close it */
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
    states.at(current_state)->clear();

    Engine::engine.data.sgv->clear();
    /* Telling the engine to stop */
    Engine::engine.data.running = false;
}
