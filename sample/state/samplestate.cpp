//
// Created by mazrog on 11/11/17.
//

#include <iostream>
#include "samplestate.hpp"

SampleState::SampleState(
    std::function<int(GameState * self)> const&   main,
    std::function<void(GameState * self)> const&  init,
    std::function<void(GameState * self)> const&  exit) :
        GameState(main, init, exit) {}


void SampleState::init() {
    GameState::init(this);
}

void SampleState::main() {
    GameState::main(this);
}

void SampleState::exit() {
    GameState::exit(this);
}