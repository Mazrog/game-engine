//
// Created by mazrog on 11/11/17.
//

#ifndef ENGINE_GAMESTATE_HPP
#define ENGINE_GAMESTATE_HPP


#include <functional>

#include "scenegraph/sg_logic.hpp"

/* Forward declaration */
class GameState;

/* Types rewriting */
using s_sgl         = std::shared_ptr<SGL>;
using s_game_state  = std::shared_ptr<GameState>;


/* Class GameState */
class GameState{
public:
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

    /* Element getters */
    SGL_Node * get(const char * name);
    Camera   * get_as_camera(const char * name);

    /* GETTERS */
    s_sgl const& get_sgl() const { return sgl; }


protected:
    std::function<void(GameState * self)>   onInit;
    std::function<int(GameState * self)>    logic;
    std::function<void(GameState * self)>   onExit;

    s_sgl        sgl;

    /* Properties */
    bool        hasBeenInit;
    bool        saved;
};

/* ---------------------------------------------------------------- */


#endif //ENGINE_GAMESTATE_HPP
