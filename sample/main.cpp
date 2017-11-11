 #include <iostream>

#include "engine.hpp"

int main() {
    Engine::init();

    Controller::State test{
            [&] {
                auto keyboard   = Engine::get_controller().eventContext.keyboard;
                SDL_Event ev;

                while(poll_event(&ev)) {
                    switch (ev.type) {
                        case SDL_KEYDOWN:
                            std::cout << "kappa" << std::endl;
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
    pause{
            [&] {
                auto keyboard   = Engine::get_controller().eventContext.keyboard;
                SDL_Event ev;

                while(poll_event(&ev)) {
                    switch (ev.type) {
                        case SDL_QUIT:
                            Engine::engine.controller.end();
                            break;
                        case SDL_KEYDOWN:
                            if (ev.key.keysym.scancode == SDL_SCANCODE_P) {
                                std::cout << "Resuming the game : P" << std::endl;
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
    };

    Engine::add_states(&test, &pause);

//    Engine::engine.controller.debug();

    Engine::start();

    return 0;
}