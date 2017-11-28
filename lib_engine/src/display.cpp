//
// Created by mazrog on 10/11/17.
//

#include <chrono>
#include <SDL2/SDL_image.h>

#include "engine.hpp"
#include "display.hpp"

Display::Display() {
    if(SDL_Init(SDL_INIT_VIDEO)){
        std::cerr << "Erreur init SDL : " << SDL_GetError() << std::endl;
    }

    if(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0){
        std::cerr << "Erreur init SDL IMG : " << IMG_GetError() << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 8);
}

Display::~Display() {
    quit(nullptr, nullptr);
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
        quit(win, ctx);
        exit(EXIT_FAILURE);
    }

    glewExperimental = true; get_error();

    if(glewInit() != GLEW_OK){
        std::cerr << "Glew initialisation error !" << std::endl;
        get_error();
        quit(win, ctx);
        return;
    }
    glGetError();

    glEnable(GL_DEPTH_TEST); get_error("enable depth");
//    glEnable(GL_CULL_FACE); get_error("enable cull");
//    glCullFace(GL_BACK); get_error("cull both");
    SDL_GL_SetSwapInterval(1);
}

void Display::quit(SDL_Window * win, SDL_GLContext ctx) {
    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    IMG_Quit();
    SDL_Quit();
}

void Display::cls() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); get_error();
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask); get_error();
}

void Display::frame() {
    SDL_GL_SwapWindow(Engine::engine.data.win);
}

void Display::render_sgv(SGV * sgv) {
    if(sgv) { sgv->render(); }
}