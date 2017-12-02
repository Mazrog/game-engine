//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_DISPLAY_HPP
#define ENGINE_DISPLAY_HPP

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scenegraph/sg_visual.hpp"

class Display {
public:
    Display();
    ~Display();

    void init(GLFWwindow * & win);

    void quit(GLFWwindow * win);

    void cls();
    void frame();

    void render_sgv(SGV * sgv);
};


#endif //ENGINE_DISPLAY_HPP
