//
// Created by mazrog on 29/12/17.
//

#include "character.hpp"
#include <events/keyboard.hpp>

Character::Character(const char * model_name, Terrain * terrain) : SGL_Node(model_name), terrain(terrain) {
    dynamicData.scale = glm::vec3(1.f);
    dynamicData.position.y += 20;
    dynamicData.update();

    renderer.setData(this);
}


void Character::move() {
    Keyboard keyboard = Keyboard::keyboard;

    int key_press = keyboard.action == GLFW_PRESS || keyboard.action == GLFW_REPEAT;
    float move_speed = 5.f;

    if(keyboard.key == GLFW_KEY_W && key_press) {
        dynamicData.position.x += move_speed;
    }

    if(keyboard.key == GLFW_KEY_S && key_press) {
        dynamicData.position.x -= move_speed;
    }

    if(keyboard.key == GLFW_KEY_A && key_press) {
        dynamicData.position.z -= move_speed;
    }

    if(keyboard.key == GLFW_KEY_D && key_press) {
        dynamicData.position.z += move_speed;
    }

    dynamicData.position.y = terrain->get_height(dynamicData.position.x, dynamicData.position.z);

    dynamicData.update();
}