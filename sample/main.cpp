#include <iostream>

#include "engine.hpp"
#include "base.hpp"

#include "rendering/renderElement.hpp"
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
                    static_cast<Camera *>(self->get("main_camera"))->move_aim(CAM_DIR::UP);
                }

                if(keyboard[SDL_SCANCODE_L]){
                    static_cast<Camera *>(self->get("main_camera"))->move_aim(CAM_DIR::RIGHT);
                }

                if(keyboard[SDL_SCANCODE_K]){
                    static_cast<Camera *>(self->get("main_camera"))->move_aim(CAM_DIR::DOWN);
                }

                if(keyboard[SDL_SCANCODE_J]){
                    static_cast<Camera *>(self->get("main_camera"))->move_aim(CAM_DIR::LEFT);
                }

                if(keyboard[SDL_SCANCODE_W]){
                    static_cast<Camera *>(self->get("main_camera"))->move_forward();
                }

                if(keyboard[SDL_SCANCODE_S]){
                    static_cast<Camera *>(self->get("main_camera"))->move_backward();
                }

                return -1;
            },
            [] (GameState * self) {
                Cube<RenderElement> * c = new Cube<RenderElement>();
//                Triangle<SimpleRender> * t =  new Triangle<SimpleRender>();
                Camera * camera = new Camera();
                camera->bind_camera(/*SimpleRender::prog.getProgId(), */RenderElement::prog.getProgId());

                self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);


//                self->bind(SG_NODE_TYPE::SG_STATIC, "triangle", t);
                self->bind(SG_NODE_TYPE::SG_STATIC, "cube", c);

            },
            [] (GameState * self) {
//                std::cout << "free main state" << std::endl;
            }
    ),
    pause ( paused_game );

    glm::vec3 center(1.f, 0.f, 0.f), point(0.f, 0.f, -1.f);

    std::cout << "POINT " << point.x << " # " << point.y << " # " << point.z << std::endl;

    apply_rot(center, point, M_PI, M_PI / 2.f);

    std::cout << "POINT " << point.x << " # " << point.y << " # " << point.z << std::endl;


//    Engine::add_states(test, pause);
//    Engine::start();

    return 0;
}