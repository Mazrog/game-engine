//
// Created by mazrog on 26/11/17.
//

#include "vector_utils.hpp"
#include "rendering/light.hpp"

Light::Light(crvec3 pos, crvec3 color, const char * name) :
        pos(pos), color(color), name(name), updated(true){}

void Light::render() {
    if(updated) {
        for (auto const & unif_light : vec_uniforms) {
            unif_light.send(pos, color);
        }
        updated = false;
    }
}

