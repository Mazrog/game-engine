//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP

#include "display.hpp"
#include "controller.hpp"

class Engine {
public:
    Engine(Engine const&) = delete;
    Engine(Engine &&) = delete;

    static Engine engine;

    /*  */
    static void init();
    static void start();

    static void delay();

    template <typename ...States>
    static void add_states(States... ts){
        engine.controller.add_states(ts...);
    }


    /* static getters */
    static Controller& get_controller() { return engine.controller; }
    static Display&    get_display() { return engine.display; }
    

    /* Attributes */
    Display      display;
    Controller   controller;

    struct Data{
        SDL_Window      * win;
        SDL_GLContext     ctx;
        SGV             * sgv;

        bool              running;

        /* Frequences */
        unsigned short    freq_disp;

        /* Destructeur */
        void clear();
    }                   data;

private:
    int    start_loop;

    /*  */
    Engine();
    void onQuit();

};


/* DEBUG SHIT */

template < class ...Args >
void pretty(Args...){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


#endif //ENGINE_ENGINE_HPP
