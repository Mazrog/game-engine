//
// Created by mazrog on 10/11/17.
//

#include <chrono>

#include "engine.hpp"
#include "display.hpp"

void get_error(const char * t){
    GLenum err;
    if((err = glGetError()) != GLEW_OK){
        std::cerr << t << std::endl;
        std::cerr << "Erreur OpenGL (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << std::endl;
    }
}

Display::Display() {
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Erreur init SDL : " << SDL_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    glEnable(GL_DEPTH_TEST);
}

void Display::init(SDL_Window *&win, SDL_GLContext &ctx) {
    win = SDL_CreateWindow(
            "Plop Engine",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            1200,
            900,
            SDL_WINDOW_OPENGL
    );
    if(!win){
        std::cerr << "Erreur init fenêtre : " << SDL_GetError() << std::endl;
        return;
    }

    ctx = SDL_GL_CreateContext(win);

    if(!ctx){
        std::cerr << "Context creation error : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(win);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    glewExperimental = true; get_error();

    if(glewInit() != GLEW_OK){
        std::cerr << "Glew initialisation error !" << std::endl;
        get_error();
        SDL_GL_DeleteContext(ctx);
        SDL_DestroyWindow(win);
        SDL_Quit();
        return;
    }
    glGetError();
    SDL_GL_SetSwapInterval(1);
}

void Display::cls() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); get_error();
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask); get_error();
}

void Display::frame() {
    SDL_GL_SwapWindow(Engine::engine.data.win);
}

void Display::render_sgv(SGV * sgv) {
    sgv->render();
}