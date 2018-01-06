//
// Created by mazrog on 11/11/17.
//

#ifndef ENGINE_GAMESTATE_HPP
#define ENGINE_GAMESTATE_HPP


#include <functional>

#include "scenegraph/sg_logic.hpp"


using MapModel = std::map<std::string, Model *>;

/* Class GameState */
class GameState{
public:
    GameState() = delete;
    GameState(
            std::function<int(GameState * self)> const&   main,
            std::function<void(GameState * self)> const&  init,
            std::function<void(GameState * self)> const&  exit
    );
    virtual ~GameState();

    /* No copy constructor */
    GameState(GameState const&) = delete;

    /* But a move one */
    GameState(GameState && gs);

    virtual void init();
    virtual void init(GameState * self);

    virtual void main();
    virtual void main(GameState * self);

    virtual void exit();
    virtual void exit(GameState * self);

    void save_state();

    /* FONCTIONS EXPOSURE */
    void bind(SG_NODE_TYPE type, const char * name, SGL_Node * node);
    void clear();
    void load_model(const char * tag, const char * file);

    /* GUI */
    void add_gui(GUI * gui);
    void gui_events();

    void set_guiManager(GuiManager * new_guiManager);

    /* Element getters */
    SGL_Node * get(const char * name);
    Camera   * get_as_camera(const char * name);

    /* GETTERS */
    SGL * const& get_sgl() const { return sgl; }
    MapModel& get_models() { return models; }
    GuiManager * get_guiManager() { return guiManager; }

protected:
    std::function<void(GameState * self)>   onInit;
    std::function<int(GameState * self)>    logic;
    std::function<void(GameState * self)>   onExit;

    SGL         * sgl;
    MapModel      models;
    GuiManager  * guiManager;

    /* Properties */
    bool        hasBeenInit;
    bool        saved;
};

/* ---------------------------------------------------------------- */


#endif //ENGINE_GAMESTATE_HPP
