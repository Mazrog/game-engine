//
// Created by mazrog on 02/12/17.
//

#include <iostream>
#include "events/mouse.hpp"

/* Callback for mouse events */
void cursor_position_callback(GLFWwindow * window, double xpos, double ypos) {
//    std::cout << "Mouse moved : " << xpos << " # " << ypos << std::endl;
    Mouse & mouse = Mouse::mouse;
    mouse.window = window;
    mouse.xpos = xpos;
    mouse.ypos = ypos;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
//    std::cout << "Button clicked : " << button << " ## " << action << std::endl;
    Mouse & mouse = Mouse::mouse;
    mouse.window = window;
    mouse.click = { button, action, mods };
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
//    std::cout << "Scroll : " << xoffset << " # " << yoffset << std::endl;
    Mouse & mouse = Mouse::mouse;
    mouse.window = window;
    mouse.scroll = { xoffset, yoffset };
}


Mouse Mouse::mouse;

Mouse::~Mouse() {}