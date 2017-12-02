#include <iostream>
#include <array>
#include <sstream>
#include <IL/il.h>
#include <events/mouse.hpp>

#include "engine.hpp"
#include "base.hpp"

#include "renderEntity.hpp"
#include "rendering/light.hpp"
#include "src/cube.hpp"
#include "terrainRender.hpp"
#include "terrain.hpp"
#include "state/samplestate.hpp"


int paused_game(GameState *){
    return -1;
}

int main_game_loop(GameState * self) {

    Keyboard keyboard = Keyboard::keyboard;

//    if (keyboard[SDL_SCANCODE_UP]) {
//        translate(self->get("cube")->get_dynamic_data().tranform,
//                  glm::vec3(0.f, .05f, 0.f));
//    }
//
//    if (keyboard[SDL_SCANCODE_DOWN]) {
//        translate(self->get("cube")->get_dynamic_data().tranform,
//                  glm::vec3(0.f, -.05f, 0.f));
//    }
//
//    if (keyboard[SDL_SCANCODE_RIGHT]) {
//        translate(self->get("cube")->get_dynamic_data().tranform,
//                  glm::vec3(.05f, 0.f, 0.f));
//    }
//
//    if (keyboard[SDL_SCANCODE_LEFT]) {
//        translate(self->get("cube")->get_dynamic_data().tranform,
//                  glm::vec3(-.05f, 0.f, 0.f));
//    }
//
//    if (keyboard[SDL_SCANCODE_I]) {
//        self->get_as_camera("main_camera")->move_aim(CAM_DIR::UP);
//    }
//
//    if (keyboard[SDL_SCANCODE_L]) {
//        self->get_as_camera("main_camera")->move_aim(CAM_DIR::RIGHT);
//    }
//
//    if (keyboard[SDL_SCANCODE_K]) {
//        self->get_as_camera("main_camera")->move_aim(CAM_DIR::DOWN);
//    }
//
//    if (keyboard[SDL_SCANCODE_J]) {
//        self->get_as_camera("main_camera")->move_aim(CAM_DIR::LEFT);
//    }
//
    if (keyboard.key == GLFW_KEY_W && keyboard.action == GLFW_PRESS) {
        self->get_as_camera("main_camera")->move_forward();
    }

    if (keyboard.key == GLFW_KEY_S && keyboard.action == GLFW_PRESS) {
        self->get_as_camera("main_camera")->move_backward();
    }

    return -1;
}

void main_game_init(GameState * self) {
//    Cube<RenderEntity> * c = new Cube<RenderEntity>();

    Terrain<TerrainRenderer>   * terrain = new Terrain<TerrainRenderer>("sample/img/thin_height_map.png");

    Camera * camera = new Camera(glm::vec3(10, 10, 10));
    camera->bind_camera(TerrainRenderer::prog.getProgId());//, RenderEntity::prog.getProgId());

    Light * sun = new Light(glm::vec3(20.f, 100.f, 20.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(TerrainRenderer::prog.getProgId() );//, RenderEntity::prog.getProgId());

    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
//    self->bind(SG_NODE_TYPE::SG_STATIC, "cube", c);
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