//
// Created by mazrog on 02/12/17.
//

#include <GLFW/glfw3.h>
#include "events/keyboard.hpp"


/* Callback for Keyboard events */
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods) {
    Keyboard::keyboard.window   = window;
    Keyboard::keyboard.key      = key;
    Keyboard::keyboard.scancode = scancode;
    Keyboard::keyboard.action   = action;
    Keyboard::keyboard.mods     = mods;
}


Keyboard Keyboard::keyboard;

