//
// Created by mazrog on 04/12/17.
//

#ifndef ENGINE_PLAYER_HPP
#define ENGINE_PLAYER_HPP

#include <scenegraph/sg_logic.hpp>
#include <events/keyboard.hpp>

template < class Render >
class Player : public SGL_Node {
public:
    Player(const char * model);
    ~Player() = default;

    void move() override;

    void render() override { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Player<Render>::Player(const char * model) : SGL_Node(model) {
    dynamicData.scale = glm::vec3(2.f);

    dynamicData.update();

    Render::init();
    renderer.setData(this);
}

template < class Render >
void Player<Render>::move() {
    Keyboard keyboard = Keyboard::keyboard;

    int key_press = keyboard.action == GLFW_PRESS || keyboard.action == GLFW_REPEAT;

    if(keyboard.key == GLFW_KEY_W && key_press) {
        dynamicData.position.x += 1;
    }

    if(keyboard.key == GLFW_KEY_S && key_press) {
        dynamicData.position.x -= 1;
    }

    if(keyboard.key == GLFW_KEY_A && key_press) {
        dynamicData.position.z -= 1;
    }

    if(keyboard.key == GLFW_KEY_D && key_press) {
        dynamicData.position.z += 1;
    }

    dynamicData.update();
}

#endif //ENGINE_PLAYER_HPP
