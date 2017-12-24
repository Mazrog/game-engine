//
// Created by mazrog on 02/12/17.
//

#include <iostream>
#include "events/mouse.hpp"

/* Callback for mouse events */
void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
    std::cout << "Mouse moved : " << xpos << " # " << ypos << std::endl;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    std::cout << "Button clicked : " << button << " ## " << action << std::endl;
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {

}

Mouse Mouse::mouse;

Mouse::Mouse() {}

Mouse::~Mouse() {}