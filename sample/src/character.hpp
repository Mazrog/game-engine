//
// Created by mazrog on 04/12/17.
//

#ifndef ENGINE_CHARACTER_HPP
#define ENGINE_CHARACTER_HPP

#include <scenegraph/sg_logic.hpp>
#include <events/keyboard.hpp>

template < class Render >
class Character : public SGL_Node {
public:
    Character(const char * model);
    ~Character() = default;

    void move() override;

    void render() override { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Character<Render>::Character(const char * model) : SGL_Node(model) {
    dynamicData.scale = glm::vec3(2.f);
    dynamicData.position.y += 20;
    dynamicData.update();

    renderer.setData(this);
}

template < class Render >
void Character<Render>::move() {
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
