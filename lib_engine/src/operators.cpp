//
// Created by mazrog on 05/01/18.
//

#include "engine.hpp"
#include "operators.hpp"

float operator"" _vpx(long double nb) {
    return nb * 2.f / Engine::engine.get_display().get_windowHeight();
}

float operator"" _hpx(long double nb) {
    return nb * 2.f / Engine::engine.get_display().get_windowWidth();
}

float operator"" _vpct(long double nb) {
    return nb * 2.f / 100.f;
}

float operator"" _hpct(long double nb) {
    return nb * 2.f / 100.f;
}