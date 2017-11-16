//
// Created by mazrog on 11/11/17.
//

#ifndef ENGINE_GAMESTATE_HPP
#define ENGINE_GAMESTATE_HPP


#include <functional>

#include "scenegraph/sg_logic.hpp"

class GameState{
public:
    GameState(
            std::function<int(GameState * self)> const&   main,
            std::function<void(GameState * self)> const&  init,
            std::function<void(GameState * self)> const&  exit
    );

    virtual ~GameState();

    virtual void init() = 0;
    virtual void init(GameState * self);

    virtual void main() = 0;
    virtual void main(GameState * self);

    virtual void exit() = 0;
    virtual void exit(GameState * self);

    /* FONCTIONS EXPOSURE */
    void bind(SG_NODE_TYPE type, const char * name, SGL_Node * node);

    /* Element getters */
    SGL_Node * get(const char * name);

    /* GETTERS */
    SGL * get_sgl() const { return sgl; }

protected:
    std::function<void(GameState * self)>   onInit;
    std::function<int(GameState * self)>    logic;
    std::function<void(GameState * self)>   onExit;

    SGL         * sgl;
};

/* ---------------------------------------------------------------- */


#endif //ENGINE_GAMESTATE_HPP
