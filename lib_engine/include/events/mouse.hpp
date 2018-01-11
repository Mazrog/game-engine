//
// Created by mazrog on 02/12/17.
//

#ifndef ENGINE_MOUSE_HPP
#define ENGINE_MOUSE_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void cursor_position_callback(GLFWwindow * window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

class Mouse {
public:
    static Mouse mouse;

public:
    ~Mouse();


    /* Attributes */
    GLFWwindow      * window;
    double            xpos;
    double            ypos;

    struct Click {
        int     button;
        int     action;
        int     mods;

    }   click;

    struct Scroll {
        double      xoffset;
        double      yoffset;

    }   scroll;

private:
    Mouse() = default;
};


#endif //ENGINE_MOUSE_HPP
