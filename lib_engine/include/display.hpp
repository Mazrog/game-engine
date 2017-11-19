//
// Created by mazrog on 10/11/17.
//

#ifndef ENGINE_DISPLAY_HPP
#define ENGINE_DISPLAY_HPP

#include <iostream>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <GL/glew.h>

#include "scenegraph/sg_visual.hpp"

class Display {
public:
    Display();
    ~Display();

    void init(SDL_Window * & win, SDL_GLContext & ctx);

    void quit(SDL_Window * win, SDL_GLContext ctx);

    void cls();
    void frame();

    void render_sgv(SGV * sgv);
};


#endif //ENGINE_DISPLAY_HPP
