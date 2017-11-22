#include <iostream>

#include "engine.hpp"
#include "base.hpp"

#include "rendering/renderElement.hpp"
#include "src/cube.hpp"
#include "procedural.hpp"
#include "plane.hpp"
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

    SampleState test(
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

                            if( ev.key.keysym.scancode == SDL_SCANCODE_RETURN) {
                                self->get_as_camera("main_camera")->disp_state();
                            }
                            break;
                        default:;
                    }
                }

                if(keyboard[SDL_SCANCODE_UP]){
                    translate(*self->get("cube")->get_dynamic_data().tranform,
                              glm::vec3(0.f, .05f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_DOWN]){
                    translate(*self->get("cube")->get_dynamic_data().tranform,
                              glm::vec3(0.f, -.05f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_RIGHT]){
                    translate(*self->get("cube")->get_dynamic_data().tranform,
                              glm::vec3(.05f, 0.f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_LEFT]){
                    translate(*self->get("cube")->get_dynamic_data().tranform,
                              glm::vec3(-.05f, 0.f, 0.f));
                }

                if(keyboard[SDL_SCANCODE_I]){
                    self->get_as_camera("main_camera")->move_aim(CAM_DIR::UP);
                }

                if(keyboard[SDL_SCANCODE_L]){
                    self->get_as_camera("main_camera")->move_aim(CAM_DIR::RIGHT);
                }

                if(keyboard[SDL_SCANCODE_K]){
                    self->get_as_camera("main_camera")->move_aim(CAM_DIR::DOWN);
                }

                if(keyboard[SDL_SCANCODE_J]){
                    self->get_as_camera("main_camera")->move_aim(CAM_DIR::LEFT);
                }

                if(keyboard[SDL_SCANCODE_W]){
                    self->get_as_camera("main_camera")->move_forward();
                }

                if(keyboard[SDL_SCANCODE_S]){
                    self->get_as_camera("main_camera")->move_backward();
                }

                return -1;
            },
            [] (GameState * self) {
                Cube<RenderElement> * c = new Cube<RenderElement>();
                Plane<Procedural>   * plane = new Plane<Procedural>();

                Camera * camera = new Camera();
                camera->bind_camera(Procedural::prog.getProgId(), RenderElement::prog.getProgId());

                self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);

                self->bind(SG_NODE_TYPE::SG_STATIC, "cube", c);

                self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", plane);

            },
            [] (GameState * self) {
            }
    ),
    pause ( paused_game );


    Engine::add_states(test, pause);
    Engine::start();
//
//    glm::vec3 pos(2.f, 0.f, 0.f);
//    glm::vec3 aim(0.f, 1.f, 0.f);
//
//    glm::vec3 tmp(aim - pos);
//
//    std::cout << aim.x << " # " << aim.y << " # " << aim.z << std::endl;
//
//    apply_rot(tmp, M_PI / 2.f, glm::vec3(0.f, 1.f, 0.f));
//    aim = pos + tmp;
//
//    std::cout << aim.x << " # " << aim.y << " # " << aim.z << std::endl;

    return 0;
}