//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_CONTROLLER_HPP
#define ENGINE_CONTROLLER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <functional>

#include "sg.hpp"

int poll_event(SDL_Event * event);

class Controller {
    /* Définition classe State */
public:
    class State{
    public:
        State(
                std::function<int()> const&   main,
                std::function<void()> const&  init = [] {},
                std::function<void()> const&  exit = [] {}
        );

        ~State() { delete sgl; };

        void init() { onInit(); }
        void main();

        SGL * get_sgl() const { return sgl; }

    private:
        /* Base functions */
        std::function<void()>   onInit;
        std::function<int()>    logic;
        std::function<void()>   onExit;

        SGL         * sgl;
    };

/* ---------------------------------------------------------------- */
public:
    Controller();

    void init();
    void start();

    /* Main loop of event controls */
    void control();
    /* ---------------------------- */

    /* Add States ---------------------------------------------------- */
    template <typename ...Trail>
    void add_states(State * s, Trail... ts){
        states.push_back(s);
        add_states(ts...);
    }
    template <typename ...Trail> void add_states() {}
    /* --------------------------------------------------------------- */

    /* SGL Functions */
    void load_sgl_from_state();
    void build_sgv_from_sgl();
    /*  */

    /* Automate functions */
    void set_state(unsigned int next_state);
    void end();
    /* -------------------- */


    /* Event structure to be accessed from States */
    struct EventContext {
        const uint8_t           * keyboard;
        std::queue<SDL_Event>     events;

    }               eventContext;
    /* ------------------------------------------ */
private:
    SGL             * sgl;

    /* States */
    std::vector<State *>    states;
    unsigned int            current_state;
};


#endif //ENGINE_CONTROLLER_HPP
