//
// Created by mazrog on 26/11/17.
//

#include "vector_utils.hpp"
#include "rendering/light.hpp"
#include <glm/glm.hpp>

Light::Light(crvec3 pos, crvec3 color, const char * name) :
        pos(pos), color(color), name(name), updated(true){}

void Light::render() {
//    if(updated) {
        glm::vec4 new_pos = dynamicData.transform * glm::vec4(pos, 1.f);
        pos = glm::vec3(new_pos);

        for (auto const & unif_light : vec_uniforms) {
            unif_light.send(pos, color);
        }
//        updated = false;
//    }
}

