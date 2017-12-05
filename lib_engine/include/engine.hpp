//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP

#include "display.hpp"
#include "controller.hpp"

/* Engine is a singleton class handling the whole game              */
/* Two bricks : a controller    -> game logic, game state, events   */
/*              a display       -> rendering the current scene      */
class Engine {
public:
    /* Deleting unused constructors */
    Engine(Engine const&) = delete;
    Engine(Engine &&) = delete;

    /* Singleton instance */
    static Engine engine;

    /* Static functions handling the state of the engine */
    static void init();
    static void start();

    /* Waiting function -> frequency of the game loop */
    static void delay();

    /* Exposing the adding states functions from the controller */
    template <typename... S>
    static void add_states(S * ... ts){
        engine.controller.add_states(ts...);
    }

    /* static getters */
    static Controller& get_controller() { return engine.controller; }
    static Display&    get_display() { return engine.display; }
    

    /* Attributes */
    Display      display;
    Controller   controller;

    /* Structure that will contain global info about the game context */
    struct Data{
        /* Rendering context */
        GLFWwindow    * win;

        /* Visual SceneGraph */
        std::unique_ptr<SGV>   sgv;

        /* Boolean handling the lifespan of the engine */
        bool              running;

        /* Frequencies */
        unsigned short    freq_disp;

        /* Destructor */
        void clear();
    }                   data;

private:
    /* private constructor */
    Engine();

    /* Freeing the ressources at the end of the engine */
    void onQuit();

};


/* DEBUG SHIT */

template < class ...Args >
void pretty(Args...){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}


#endif //ENGINE_ENGINE_HPP
