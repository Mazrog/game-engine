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

void apply_rot(glm::vec3 & point, crfloat angle, crvec3 axis) {
    glm::mat4 rot;
    rot = glm::rotate(rot, angle, axis);

    point = glm::vec3(rot * glm::vec4(point, 1.f));
}

glm::vec3 pdt_vec(crvec3 u, crvec3 v) {
    glm::vec3 res;
    res.x = u.y*v.z - u.z*v.y;
    res.y = u.z*v.x - u.x*v.z;
    res.z = u.x*v.y - u.y*v.x;

    return res;
}