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


int paused_game(GameState *){
    Keyboard keyboard = Keyboard::keyboard;

    if(keyboard.key == GLFW_KEY_R && keyboard.action == GLFW_PRESS) {
        std::cout << "Resuming the game" << std::endl;
        return 0;
    }

    return -1;
}

int main_game_loop(GameState * self) {
    Keyboard keyboard = Keyboard::keyboard;

    if(keyboard.key == GLFW_KEY_ESCAPE && keyboard.action == GLFW_PRESS) {
        /* Exiting the game */
        Engine::engine.get_controller().end();
        return -1;
    }

    if(keyboard.key == GLFW_KEY_P && keyboard.action == GLFW_PRESS) {
        std::cout << "pausing the game" << std::endl;
        self->save_state();
        return 1;
    }

    self->get_as_camera("main_camera")->move();

    return -1;
}

void main_game_init(GameState * self) {
    Terrain<TerrainRenderer>   * terrain = new Terrain<TerrainRenderer>("sample/img/thin_height_map.png");

    Camera * camera = new Camera(glm::vec3(10, 10, 10));
    camera->bind_camera(TerrainRenderer::prog.getProgId());//, RenderEntity::prog.getProgId());

    Light * sun = new Light(glm::vec3(20.f, 100.f, 20.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(TerrainRenderer::prog.getProgId() );//, RenderEntity::prog.getProgId());

    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
    self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", terrain);
}


int main() {
    Engine::init();

    GameState test(
            main_game_loop,
            main_game_init,
            [] (GameState *) {}
    ),
    pause ( paused_game, [] (GameState *) {}, [] (GameState *) {} );


    Engine::add_states(test, pause);
    Engine::start();


    return 0;
}