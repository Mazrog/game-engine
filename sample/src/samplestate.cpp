//
// Created by mazrog on 11/11/17.
//

#include <iostream>
#include "../include/samplestate.hpp"

SampleState::SampleState(
    std::function<int()> const&   main,
    std::function<void()> const&  init,
    std::function<void()> const&  exit) :
        GameState(main, init, exit) {}


void SampleState::init() {
    GameState::init();
}

void SampleState::main() {
    GameState::main();
}

void SampleState::exit() {
    GameState::exit();
}