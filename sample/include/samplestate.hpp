//
// Created by mazrog on 11/11/17.
//

#ifndef ENGINE_SAMPLESTATE_HPP
#define ENGINE_SAMPLESTATE_HPP

#include "gamestate.hpp"

class SampleState : public GameState {
public:
    explicit SampleState(
            std::function<int()> const&   main,
            std::function<void()> const&  init = [] {},
            std::function<void()> const&  exit = [] {}
    );

    ~SampleState() = default;

    void init() override;
    void main() override;
    void exit() override;
};


#endif //ENGINE_SAMPLESTATE_HPP
