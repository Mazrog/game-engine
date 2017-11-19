//
// Created by mazrog on 19/11/17.
//

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "base.hpp"
#include "vector_utils.hpp"


void angle_between(crvec3 u, crvec3 v, float & pitch, float & yaw) {
    /* Pitch    -> UP / DOWN    */
    /* YAW      -> RIGHT / LEFT */
    glm::vec2   xy = glm::vec2(u.x, u.y) - glm::vec2(v.x, v.y),
            xz = glm::vec2(u.x, u.z) - glm::vec2(v.x, v.z);

    pitch = std::atan2(xy.y, xy.x);
    yaw   = std::atan2(xz.y, xz.x);
}

void apply_rot(crvec3 center, glm::vec3 & point, crfloat pitch, crfloat yaw) {
    glm::mat4 rot;
    rot = glm::rotate(rot, pitch, glm::vec3(0.f, 0.f, 1.f));
    rot = glm::rotate(rot, yaw,   glm::vec3(0.f, 1.f, 0.f));

    point = center + glm::vec3(rot * glm::vec4(point, 1.f));
}