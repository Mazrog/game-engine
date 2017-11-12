//
// Created by mazrog on 11/11/17.
//

#ifndef ENGINE_GAMESTATE_HPP
#define ENGINE_GAMESTATE_HPP


#include <functional>

#include "scenegraph/scenegraph.hpp"

class GameState{
public:
    GameState(
            std::function<int()> const&   main,
            std::function<void()> const&  init,
            std::function<void()> const&  exit
    );

    virtual ~GameState();

    virtual void init() = 0;
    virtual void main() = 0;
    virtual void exit() = 0;

    SGL * get_sgl() const { return sgl; }

protected:
    std::function<void()>   onInit;
    std::function<int()>    logic;
    std::function<void()>   onExit;

    SGL         * sgl;
};

/* ---------------------------------------------------------------- */


#endif //ENGINE_GAMESTATE_HPP
