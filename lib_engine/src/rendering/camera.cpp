//
// Created by mazrog on 13/11/17.
//


#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <base.hpp>
#include <engine.hpp>

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
    target = nullptr;
    look_speed = .05f;
    move_speed = .05f;
    d_roll = d_yaw = d_pitch = 0.f;

    Display& display = Engine::engine.get_display();
    set_carac(70.f, display.get_windowWidth() / (float) display.get_windowHeight());
    update();
    updated = true;
}

void Camera::render() {
    if(updated || target) {
        update();

        for (auto const &uniform : vec_uniform) {
            uniform.send(pos, cam_mat);
        }
    }
}

void Camera::update() {
    if( target ) {
        glm::vec3 target_pos = target->get_dynamic_data().position;

        aim = target_pos + glm::vec3(0.f, 3.f, 0.f);

        pos = target_pos;
        pos.x -= dist_from_target;
        pos.y = aim.y + dist_from_target * sinf(glm::radians(0.f));

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
    if ( target ) {
        dist_from_target = (dist_from_target <= 1.f) ? 1.f : dist_from_target - .5f;
    } else {
        glm::vec3 qte = move_speed * (aim - pos);
        pos += qte;
    }
    updated = true;
}

void Camera::move_backward() {
    if ( target ) {
        dist_from_target = (dist_from_target > 40) ? 40.f : dist_from_target + .5f;
    } else {
        glm::vec3 qte = move_speed * (aim - pos);
        pos -= qte;
    }
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

void Camera::follow(SGL_Node *target_elem) {
    target = target_elem;
    dist_from_target = 10;

    update();
}

void Camera::move() {
    Keyboard keyboard = Keyboard::keyboard;
    Mouse    mouse    = Mouse::mouse;

    int key_press = keyboard.action == GLFW_PRESS || keyboard.action == GLFW_REPEAT;

    if (keyboard.key == GLFW_KEY_I && key_press) {
        move_aim(CAM_DIR::UP);
    }

    if (keyboard.key == GLFW_KEY_L && key_press) {
        move_aim(CAM_DIR::RIGHT);
    }

    if (keyboard.key == GLFW_KEY_K && key_press) {
        move_aim(CAM_DIR::DOWN);
    }

    if (keyboard.key == GLFW_KEY_J && key_press) {
        move_aim(CAM_DIR::LEFT);
    }

    if (keyboard.key == GLFW_KEY_UP && key_press) {
        move_forward();
    }

    if (keyboard.key == GLFW_KEY_DOWN && key_press) {
        move_backward();
    }

    if ( mouse.click.button == GLFW_MOUSE_BUTTON_LEFT ) {
      if ( mouse.click.action == GLFW_RELEASE ) {
          last_click = {-1, -1};
      } else {
          if ( last_click.x < 0.f || last_click.y < 0.f ) {
              last_click = { mouse.xpos, mouse.ypos };
          } else {
              std::cout << "kappa" << std::endl;
          }
      }
    }

}