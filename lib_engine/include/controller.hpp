//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_CONTROLLER_HPP
#define ENGINE_CONTROLLER_HPP

#include <iostream>
#include <vector>
#include <queue>

#include "gamestate.hpp"
#include "scenegraph/scenegraph.hpp"
#include "events/mouse.hpp"
#include "events/keyboard.hpp"


class Controller {
public:
    Controller();
    ~Controller();

    /* Startup functions to init the context */
    void init();
    void start();

    /* Main loop of event controls */
    void control();
    /* ---------------------------- */

    /* Add States ---------------------------------------------------- */
    template <typename ...Trail>
    void add_states(GameState * s, Trail && ... ts){
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


private:
    SGL                                         * sgl;

    /* States */
    std::vector<GameState *>                    states;
    unsigned int                                current_state;
};


#endif //ENGINE_CONTROLLER_HPP
