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

    int get_windowWidth() const { return window_width; }
    int get_windowHeight() const { return window_height; }

private:
    int     window_width;
    int     window_height;
};


#endif //ENGINE_DISPLAY_HPP
