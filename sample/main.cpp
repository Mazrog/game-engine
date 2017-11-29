#include <iostream>
#include <array>
#include <sstream>

#include "engine.hpp"
#include "base.hpp"

#include "rendering/renderElement.hpp"
#include "rendering/light.hpp"
#include "src/cube.hpp"
#include "terrainRender.hpp"
#include "terrain.hpp"
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

int main_game_loop(GameState * self) {
    auto keyboard = Engine::get_controller().eventContext.keyboard;
    SDL_Event ev;

    while (poll_event(&ev)) {
        switch (ev.type) {
            case SDL_KEYDOWN:
                if (ev.key.keysym.scancode == SDL_SCANCODE_P) {
                    std::cout << "Pausing the game" << std::endl;
                    self->save_state();
                    return 1;
                }
                break;
            default:;
        }
    }

    rotate(self->get("cube")->get_dynamic_data().tranform, 1, glm::vec3(0.0, 1.0, 0.0));
//    rotate(self->get("sun")->get_dynamic_data().tranform, -1, glm::vec3(0.0, 1.0, 0.0));

    if (keyboard[SDL_SCANCODE_UP]) {
        translate(self->get("cube")->get_dynamic_data().tranform,
                  glm::vec3(0.f, .05f, 0.f));
    }

    if (keyboard[SDL_SCANCODE_DOWN]) {
        translate(self->get("cube")->get_dynamic_data().tranform,
                  glm::vec3(0.f, -.05f, 0.f));
    }

    if (keyboard[SDL_SCANCODE_RIGHT]) {
        translate(self->get("cube")->get_dynamic_data().tranform,
                  glm::vec3(.05f, 0.f, 0.f));
    }

    if (keyboard[SDL_SCANCODE_LEFT]) {
        translate(self->get("cube")->get_dynamic_data().tranform,
                  glm::vec3(-.05f, 0.f, 0.f));
    }

    if (keyboard[SDL_SCANCODE_I]) {
        self->get_as_camera("main_camera")->move_aim(CAM_DIR::UP);
    }

    if (keyboard[SDL_SCANCODE_L]) {
        self->get_as_camera("main_camera")->move_aim(CAM_DIR::RIGHT);
    }

    if (keyboard[SDL_SCANCODE_K]) {
        self->get_as_camera("main_camera")->move_aim(CAM_DIR::DOWN);
    }

    if (keyboard[SDL_SCANCODE_J]) {
        self->get_as_camera("main_camera")->move_aim(CAM_DIR::LEFT);
    }

    if (keyboard[SDL_SCANCODE_W]) {
        self->get_as_camera("main_camera")->move_forward();
    }

    if (keyboard[SDL_SCANCODE_S]) {
        self->get_as_camera("main_camera")->move_backward();
    }

    return -1;
}

void main_game_init(GameState * self) {
    Cube<RenderElement> * c = new Cube<RenderElement>();

    Terrain<TerrainRenderer>   * terrain = new Terrain<TerrainRenderer>();

    Camera * camera = new Camera();
    camera->bind_camera(TerrainRenderer::prog.getProgId(), RenderElement::prog.getProgId());

    Light * sun = new Light(glm::vec3(10.f, 5.f, 10.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(TerrainRenderer::prog.getProgId(), RenderElement::prog.getProgId());

    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
    self->bind(SG_NODE_TYPE::SG_STATIC, "cube", c);
    self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", terrain);
}


int main() {
    Engine::init();

    SampleState test(
            main_game_loop,
            main_game_init
    ),
    pause ( paused_game );


    Engine::add_states(test, pause);
    Engine::start();


    return 0;
}