#include <iostream>

#include "engine.hpp"
#include "base.hpp"

#include "rendering/renderElement.hpp"
#include "rendering/simpleRender.hpp"
#include "src/cube.hpp"
#include "src/triangle.hpp"
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
            [] (GameState * self) {
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

                if(keyboard[SDL_SCANCODE_UP]){
                    translate(*self->get("triangle")->get_dynamic_data().tranform,
                              glm::vec3(0.f, .05f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_DOWN]){
                    translate(*self->get("triangle")->get_dynamic_data().tranform,
                              glm::vec3(0.f, -.05f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_RIGHT]){
                    translate(*self->get("triangle")->get_dynamic_data().tranform,
                              glm::vec3(.05f, 0.f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_LEFT]){
                    translate(*self->get("triangle")->get_dynamic_data().tranform,
                              glm::vec3(-.05f, 0.f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_S]){
                    scale(*self->get("triangle")->get_dynamic_data().tranform,
                              glm::vec3(0.97f, 1.f, 1.f));
                }

                if(keyboard[SDL_SCANCODE_D]){
                    scale(*self->get("triangle")->get_dynamic_data().tranform,
                          glm::vec3(1.03f, 1.f, 1.f));
                }

                if(keyboard[SDL_SCANCODE_E]){
                    std::cout << "plop" << std::endl;
                }

                return -1;
            },
            [] (GameState * self) {
                Cube<RenderElement> * c = new Cube<RenderElement>();
                self->bind(SG_NODE_TYPE::SG_STATIC, "cube", c);


                Triangle<SimpleRender> * t =  new Triangle<SimpleRender>();
                self->bind(SG_NODE_TYPE::SG_STATIC, "triangle", t);


                Camera * camera = new Camera();
                self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
            },
            [] (GameState * self) {
                delete self->get("cube");
                delete self->get("triangle");
                delete self->get("main_camera");
            }
    },
    pause{ paused_game };


    Engine::add_states(&test, &pause);
    Engine::start();

    return 0;
}