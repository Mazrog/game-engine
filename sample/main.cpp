#include <iostream>
#include <vector>
#include <sstream>

#include <events/mouse.hpp>
#include <engine.hpp>
#include <base.hpp>
#include <gui/elements/table.hpp>
#include <rendering/entity.hpp>

#include "rendering/renderer/renderEntity.hpp"
#include "rendering/light.hpp"
#include "terrain.hpp"
#include "character.hpp"

#include "gui/elements/guibox.hpp"
#include "gui/elements/textblock.hpp"
#include "gui/characterPanel.hpp"
#include "gui/button.hpp"
#include "gui/guiManagers/mainGuiManager.hpp"
#include "skybox.hpp"


void main_game_guiEvents(GuiManager * gm, GameState *) {
    Keyboard keyboard = Keyboard::keyboard;

    if( keyboard.key == GLFW_KEY_B && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("inventory")->hide();
        } else {
            gm->get_guis().at("inventory")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_C && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("characterPanel")->hide();
        } else {
            gm->get_guis().at("characterPanel")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_H && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("help")->hide();
        } else {
            gm->get_guis().at("help")->show();
        }
    }
}

void main_menu_guiEvents(GuiManager * gm, GameState *) {
    Keyboard keyboard   = Keyboard::keyboard;
    Mouse  mouse        = Mouse::mouse;

    if( keyboard.key == GLFW_KEY_C && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("aalayer")->hide();
        } else {
            gm->get_guis().at("aalayer")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_V && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("classes_tree")->hide();
        } else {
            gm->get_guis().at("classes_tree")->show();
        }
    }

    if( keyboard.key == GLFW_KEY_B && keyboard.action == GLFW_PRESS ) {
        if ( keyboard.mods == GLFW_MOD_SHIFT ) {
            gm->get_guis().at("model_viewer")->hide();
        } else {
            gm->get_guis().at("model_viewer")->show();
        }
    }

    /*  */

}

void main_menu_init(GameState * self) {
    /* Models */
    self->load_model("elf", "sample/obj/character/nightelffemale/nightelffemale.obj");

    /* Character Buffer */
    auto * character = new Character("elf", nullptr);
    self->bind(SG_NODE_TYPE::SG_STATIC, "character", character);


    /* GUIS */
    /* Just to have a pattern for the final result */
    auto * menu = new Guibox("aalayer", L"", "sample/img/gui/create_perso.jpg", glm::vec2(-1.f, 1.f), glm::vec2(2.f));
    self->set_guiManager(new MainGuiManager(self, main_menu_guiEvents));

    Loader::JsonData data = Loader::parse_json_data("sample/assets/world.json");
    glm::vec3 fontColor = glm::vec3(1.f);

    auto kappa = std::vector<std::wstring>();
    kappa.emplace_back(L"Humains");
    kappa.emplace_back(L"Nains");
    kappa.emplace_back(L"Elfes");

    auto * content = new Guibox("content", L"");

    /* Right Sidebar */


    /* Race chooser */
    for(unsigned i = 0; i < kappa.size(); ++i ) {
        content->add(new Button("", kappa.at(i), "sample/img/gui/green_cell.png", glm::vec2(-1.f + (i * 392.0_hpx), 1.f),
                                   glm::vec2(392.0_hpx, 135.0_vpx), 36, fontColor, GL_RGBA), false);
    }

    /* Classes Tree */
    auto * class_tree = new Guibox("class_tree", L"Classes", "sample/img/gui/green_cell.png", glm::vec2(-1.f, 1.f - 135.0_vpx),
                                   glm::vec2(705.0_hpx, 915.0_vpx), GL_RGBA);

    content->add(class_tree, false);

    /* Model Viewer */
    auto * model_viewer = new Guibox("model_viewer", L"", "sample/img/gui/green_cell.png",
                                     glm::vec2(-1.f + 705.0_hpx, 1.f - 135.0_vpx),
                                     glm::vec2(470.0_hpx, 915.0_vpx), GL_RGBA);

    content->add(model_viewer, false);

    /* ---------------------- */
    menu->show();
    self->add_gui(menu);

    content->show();
    self->add_gui(content);
}

int main_menu_loop(GameState * self) {
    Keyboard keyboard = Keyboard::keyboard;

    if(keyboard.key == GLFW_KEY_ESCAPE && keyboard.action == GLFW_PRESS) {
        /* Exiting the game */
        Engine::engine.get_controller().end();
        return -1;
    }

    if(keyboard.key == GLFW_KEY_ENTER && keyboard.action == GLFW_PRESS) {
        return 0;
    }

    self->gui_events();

    /*  ---------------------  */



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

    if ( keyboard.key == GLFW_KEY_RIGHT ) {
        rotate(self->get("tree")->get_dynamic_data().transform, 1.f, glm::vec3(0, 1, 0));
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

    terrain->load_terrain_from_file("sample/assets/first.json", self);

    /* SkyBox(es) */
    auto skybox = new Skybox("day_1", "sample/img/skybox/sky_1");
    self->bind(SG_NODE_TYPE::SG_STATIC, "skybox", skybox);

    /* Misc : Cameras and lights */
    Camera * camera = new Camera(glm::vec3(50, 50, 50), glm::vec3(0, 50, 0));
    camera->bind_camera(RenderEntity::prog.getProgId(),
                        SkyboxRender::prog.getProgId());
    camera->follow(player);

    Light * sun = new Light(glm::vec3(20.f, 100.f, 20.f), glm::vec3(.788f, .886f, 1.f));
    sun->bind_light(RenderEntity::prog.getProgId());


    /* Binding */
    self->bind(SG_NODE_TYPE::SG_CAMERA, "main_camera", camera);
    self->bind(SG_NODE_TYPE::SG_LIGHT, "sun", sun);
    self->bind(SG_NODE_TYPE::SG_STATIC, "terrain", terrain);
    self->bind(SG_NODE_TYPE::SG_DYNAMIC, "player", player);

    /* Loading GUI */
    auto * inventory = new Guibox("inventory", L"Inventaire",
                                    "sample/img/gui/box.png", glm::vec2(.2f, .35f),
                                    glm::vec2(.65f, 1.1f), GL_RGBA);

    auto * char_panel = new CharacterPanel(player);

    auto * help = new Guibox("help", L"Aide", "sample/img/gui/box.png",
                               glm::vec2(-.5f, 1.f),
                               glm::vec2(1.f, .37f), GL_RGBA);
    /*
    help->add(new TextBlock("",
                            L"W, A, S, D pour déplacer le joueur\n\nPour fermer une fenêtre, SHIFT + [Touche correspondante]\n\
C : Informations personnage\nH : Aide\nB : Inventaire"
              )
    );
     */

    help->add(new TextBlock("", L"Héros : Archimage"));

//    help->show();
//    char_panel->show();

    self->set_guiManager(new MainGuiManager(self, main_game_guiEvents));

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