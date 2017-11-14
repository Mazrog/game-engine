#include <iostream>

#include "engine.hpp"

#include "rendering/renderElement.hpp"
#include "src/cube.hpp"
#include "state/samplestate.hpp"

int paused_game(GameState *){
    auto keyboard   = Engine::get_controller().eventContext.keyboard;
    SDL_Event ev;

    while(poll_event(&ev)) {
        switch (ev.type) {
            case SDL_KEYDOWN:
                if (ev.key.keysym.scancode == SDL_SCANCODE_P) {
                    std::cout << "Resuming the game" << std::endl;
                    return 0;
                }
                break;
            default:;
        }
    }

    if(keyboard[SDL_SCANCODE_R]){
        std::cout << "Etat de pause : R" << std::endl;
    }

    return -1;
}

int main() {
    Engine::init();

    SampleState test{
            [] (GameState *) {
                auto keyboard   = Engine::get_controller().eventContext.keyboard;
                SDL_Event ev;

                while(poll_event(&ev)) {
                    switch (ev.type) {
                        case SDL_KEYDOWN:
                            if (ev.key.keysym.scancode == SDL_SCANCODE_P) {
                                std::cout << "Pausing the game" << std::endl;
                                return 1;
                            }
                            break;
                        default:;
                    }
                }

                if(keyboard[SDL_SCANCODE_E]){
                    std::cout << "plop" << std::endl;
                }

                return -1;
            }
    },
    pause{ paused_game };

    /*  */
    Cube<RenderElement> * c = new Cube<RenderElement>();

    test.bind(SG_NODE_TYPE::SG_STATIC, "cube", c);

    /* ----------- */

    Engine::add_states(&test, &pause);

    Engine::start();


    delete c;

    return 0;
}