//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_DISPLAY_HPP
#define ENGINE_DISPLAY_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "scenegraph/scenegraph.hpp"

void get_error(const char * t = "");

class Display {
public:
    Display();

    void init(SDL_Window * & win, SDL_GLContext & ctx);

    void cls();
    void frame();

    void render_sgv(SGV * sgv);

private:
    /* Render variables */
    GLuint      prog;
    GLuint      vao;
    GLuint      vbo;
};


#endif //ENGINE_DISPLAY_HPP
