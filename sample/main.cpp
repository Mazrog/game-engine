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

#include "gui/elements/guibox.hpp"
#include "gui/elements/textblock.hpp"
#include "gui/characterPanel.hpp"
#include "skybox.hpp"


void main_menu_init(GameState * self) {
    auto menu = new Guibox("menu", "", "sample/img/gui/create_perso.jpg", glm::vec2(-1.f, 1.f), glm::vec2(2.f));
    menu->show();

    self->add_gui(menu);
}

int main_menu_loop(GameState *) {
    Keyboard keyboard = Keyboard::keyboard;

    if(keyboard.key == GLFW_KEY_ESCAPE && keyboard.action == GLFW_PRESS) {
        /* Exiting the game */
        Engine::engine.get_controller().end();
        return -1;
    }

    if(keyboard.key == GLFW_KEY_ENTER && keyboard.action == GLFW_PRESS) {
        return 0;
    }

    return  -1;
}

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

    if(keyboard.key == GLFW_KEY_KP_0 && keyboard.action == GLFW_PRESS) {
        return 2;
    }

    self->get("player")->move();
    self->get_as_camera("main_camera")->move();

    self->gui_events();

    return -1;
}

void main_game_init(GameState * self) {
    /* Models */
    self->load_model("elf", "sample/obj/character/nightelffemale/nightelffemale.obj");

    /* Entities */
    auto terrain = new Terrain("sample/img/thin_height_map.png");
    auto player = new Character("elf", terrain);

    /* SkyBox(es) */
    auto skybox = new Skybox("day_1", "sample/img/skybox/sky_1");

    self->bind(SG_NODE_TYPE::SG_STATIC, "skybox", skybox);

    /* Misc : Cameras and lights */
    Camera * camera = new Camera(glm::vec3(50, 50, 50), glm::vec3(0, 50, 0));
    camera->bind_camera(TerrainRenderer::prog.getProgId(),
                        RenderEntity::prog.getProgId(),
                        SkyboxRender::prog.getProgId());
    camera->follow(player);

    Light * sun = new Light(glm::vec3(20.f, 100.f, 20.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(TerrainRenderer::prog.getProgId(), RenderEntity::prog.getProgId());


    /* Binding */
    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
    self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", terrain);
    self->bind(SG_NODE_TYPE::SG_DYNAMIC, "player", player);

    /* Loading GUI */
    auto * inventory = new Guibox("inventory", "Inventaire",
                                    "sample/img/gui/box.png", glm::vec2(.2f, .35f),
                                    glm::vec2(.65f, 1.1f), GL_RGBA);

    auto * char_panel = new CharacterPanel(player);

    auto * help = new Guibox("help", "Aide", "sample/img/gui/box.png",
                               glm::vec2(-.5f, 1.f),
                               glm::vec2(1.f, .37f), GL_RGBA);
//    help->add(new TextBlock("",
//                            L"W, A, S, D pour déplacer le joueur\n\nPour fermer une fenêtre, SHIFT + [Touche correspondante]\n\
//C : Informations personnage\nH : Aide\nB : Inventaire"
//              )
//    );

    auto data = Loader::parse_json_data("sample/assets/t.json")["name"];

    help->add(new TextBlock("", data.at(0)));

//    help->show();
//    char_panel->show();

    self->add_gui(inventory);
    self->add_gui(char_panel);
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

//    Loader::parse_json_data("sample/assets/t.json");

    return 0;
}