#include <iostream>
#include <array>
#include <sstream>

#include <events/mouse.hpp>
#include <engine.hpp>
#include <base.hpp>

#include "renderEntity.hpp"
#include "rendering/light.hpp"
#include "terrainRender.hpp"
#include "terrain.hpp"
#include "character.hpp"

#include "gui/guibox.hpp"
#include "gui/textblock.hpp"
#include "gui/table.hpp"


void main_menu_init(GameState *) {}

int main_menu_loop(GameState *) { return  -1; }

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

    self->get("player")->move();
    self->get_as_camera("main_camera")->move();

    self->gui_events();

    return -1;
}

void main_game_init(GameState * self) {
    self->load_model("elf", "sample/obj/character/nightelffemale/nightelffemale.obj");

    auto terrain = new Terrain<TerrainRenderer>("sample/img/thin_height_map.png");
    auto player = new Character<RenderEntity>("elf");

    Camera * camera = new Camera(glm::vec3(50, 50, 50), glm::vec3(0, 50, 0));
    camera->bind_camera(TerrainRenderer::prog.getProgId(), RenderEntity::prog.getProgId());
    camera->follow(player);

    Light * sun = new Light(glm::vec3(20.f, 100.f, 20.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(TerrainRenderer::prog.getProgId(), RenderEntity::prog.getProgId());

    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
    self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", terrain);
    self->bind(SG_NODE_TYPE::SG_DYNAMIC, "player", player);

    /* Loading GUI */
    Guibox * inventory = new Guibox("inventory", "Inventaire",
                                    "sample/img/gui/box.png", glm::vec2(.2f, .35f),
                                    glm::vec2(.65f, 1.1f), GL_RGBA);
    Guibox * char_info = new Guibox("charInfo", "Personnage",
                                    "sample/img/crate.jpg", glm::vec2(-.999f, .52f),
                                    glm::vec2(.55f, 1.1f), GL_RGB);
//    Guibox * help = new Guibox("help", "Aide",
//                               "sample/img/gui/box.png", glm::vec2(-.5f, .99f),
//                               glm::vec2(1.f, .37f), GL_RGBA);

    auto * help = new Table("help", "Aide", 4, 2, "sample/img/gui/box.png",
                               glm::vec2(-.5f, .99f),
                               glm::vec2(1.f, .37f), GL_RGBA);
    help->add_cell(0, new TextBlock("a", L"Caractéristiques : "));
    help->add_cell(1, new TextBlock("b", L"Force :"));
    help->add_cell(1, new TextBlock("c", L"12"));
    help->add_cell(2, new TextBlock("d", L"Endurance :"));
    help->add_cell(2, new TextBlock("e", L"17"));
    help->add_cell(3, new TextBlock("e", L"Dextérité : "));
    help->add_cell(3, new TextBlock("f", L"21"));
    help->show();

    self->add_gui(inventory);
    self->add_gui(char_info);
    self->add_gui(help);
}

void main_game_exit(GameState * self) {
    for(auto & pair: self->get_sgl()->graph) {
        delete pair.second;
    }
}


int main() {
    Engine::init();

    GameState * game = new GameState(
            main_game_loop,
            main_game_init,
            main_game_exit
    ),
    *pause = new GameState( paused_game, [] (GameState *) {}, [] (GameState *) {} ),
    *main_menu = new GameState(main_menu_loop, main_menu_init, [] ( GameState * ) {});


    Engine::add_states(game, pause, main_menu);
    Engine::start();

    return 0;
}