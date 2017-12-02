//
// Created by mazrog on 13/11/17.
//


#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <base.hpp>

#include "rendering/camera.hpp"
#include "events/keyboard.hpp"
#include "events/mouse.hpp"

Camera::Camera(const char * name) : SGL_Node(-1),
                                    pos(5.f, 2.f, 5.f), aim(0.f), up(0.f, 1.f, 0.f),
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
    look_speed = .05f;
    move_speed = .1f;
    d_roll = d_yaw = d_pitch = 0.f;

    set_carac();
    update();
    updated = true;
}

void Camera::render() {
    if(updated) {
        update();

        for (auto const &uniform : vec_uniform) {
            uniform.send(pos, cam_mat);
        }
    }
}

void Camera::update() {
    if( target ) {
        glm::mat4 target_transform = target->get_dynamic_data().tranform;
        glm::vec4 target_pos = target_transform[0];

        std::cout << target_pos.x << " # " << target_pos.y << " # " << target_pos.z << std::endl;

    } else {
        glm::vec3 tengent = glm::normalize(pdt_vec(aim - pos, up));
        glm::vec3 tmp(aim - pos), tmp_up(up);

        apply_rot(up, d_pitch, tengent);
        apply_rot(tmp, d_pitch, tengent);
        apply_rot(up, d_yaw, glm::vec3(0.f, 1.f, 0.f));
        apply_rot(tmp, d_yaw, glm::vec3(0.f, 1.f, 0.f));
        aim = (pos + tmp);
    }

    glm::mat4 lookat = glm::lookAt(pos, aim, up);
    cam_mat = perspective * lookat;


    d_pitch = d_yaw = d_roll = 0;
    updated = false;
}

void Camera::set_carac(const float &angle_rad, const float &ratio, const float &near, const float &far) {
    perspective = glm::perspective(glm::radians(angle_rad), ratio, near, far);
}

/* Move functions */

void Camera::move_forward() {
    glm::vec3 qte =  move_speed * (aim - pos);
    pos += qte;
    aim += qte;
    updated = true;
}

void Camera::move_backward() {
    glm::vec3 qte =  move_speed * (aim - pos);
    pos -= qte;
    aim -= qte;
    updated = true;
}

void Camera::move_aim(const short &direction) {
    /* Move yaw, pitch, roll */
    int v_sign = 0,
        h_sign = 0;
    switch (direction) {
        case CAM_DIR::UP:
            v_sign = 1;
            break;
        case CAM_DIR::RIGHT:
            h_sign = -1;
            break;
        case CAM_DIR::DOWN:
            v_sign = -1;
            break;
        case CAM_DIR::LEFT:
            h_sign = 1;
            break;
        default:;
    }

    d_pitch = v_sign * look_speed;
    d_yaw = h_sign * look_speed;
    updated = true;
}

void Camera::move() {
    Keyboard keyboard = Keyboard::keyboard;

    if (keyboard.key == GLFW_KEY_I && keyboard.action == GLFW_PRESS) {
        move_aim(CAM_DIR::UP);
    }

    if (keyboard.key == GLFW_KEY_L && keyboard.action == GLFW_PRESS) {
        move_aim(CAM_DIR::RIGHT);
    }

    if (keyboard.key == GLFW_KEY_K && keyboard.action == GLFW_PRESS) {
        move_aim(CAM_DIR::DOWN);
    }

    if (keyboard.key == GLFW_KEY_J && keyboard.action == GLFW_PRESS) {
        move_aim(CAM_DIR::LEFT);
    }

    if (keyboard.key == GLFW_KEY_W && keyboard.action == GLFW_PRESS) {
        move_forward();
    }

    if (keyboard.key == GLFW_KEY_S && keyboard.action == GLFW_PRESS) {
        move_backward();
    }
}