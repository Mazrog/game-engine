//
// Created by mazrog on 13/11/17.
//


#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

#include "rendering/camera.hpp"

Camera::Camera(const char * name) : SGL_Node(-1),
                                    pos(2.f, 0.f, 2.f), aim(0.f), up(0.f, 1.f, 0.f),
                                    name(name) {
    init();
}

Camera::Camera(const glm::vec3 &pos, const glm::vec3 &aim, const glm::vec3 &up, const char * name) :
        pos(pos),
        aim(aim),
        up(up),
        name(name){
    init();
}

void Camera::init() {
    dynamicData.tranform = nullptr;
    look_speed = .1f;
    move_speed = .01f;

    angle_between(pos, aim, pitch, yaw);

    std::cout << pitch << " ## " << yaw << std::endl;

    set_carac();
}

void Camera::render() {
    glm::mat4 cam_mat = perspective*glm::lookAt(pos, aim, up);

    for(auto const& uniform : vec_uniform){
        uniform.send(cam_mat);
    }
}

void Camera::set_carac(const float &angle_rad, const float &ratio, const float &near, const float &far) {
    perspective = glm::perspective(glm::radians(angle_rad), ratio, near, far);
}

/* Move functions */

void Camera::move_forward() {
    pos += move_speed * (aim - pos);
}

void Camera::move_backward() {
    pos -= move_speed * (aim - pos);
}

void Camera::move_aim(const short &direction) {

}