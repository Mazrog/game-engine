//
// Created by mazrog on 02/12/17.
//

#ifndef ENGINE_KEYBOARD_HPP
#define ENGINE_KEYBOARD_HPP

#include <GLFW/glfw3.h>

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods);

class Keyboard {
public:
    static Keyboard keyboard;

public:
    ~Keyboard() = default;


    GLFWwindow  * window;
    int           key;
    int           scancode;
    int           action;
    int           mods;

private:
    Keyboard() = default;
};


#endif //ENGINE_KEYBOARD_HPP
