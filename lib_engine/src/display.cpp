//
// Created by mazrog on 10/11/17.
//

#include <chrono>

#include "engine.hpp"
#include "display.hpp"
#include "utils.hpp"

Display::Display() {
    if(!glfwInit()){
        std::cerr << "GLFW INIT error" << std::endl;
    }

    glfwSetErrorCallback(glfw_error_callback);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_DEPTH_BITS, 8);
}

Display::~Display() {
    quit(nullptr);
}

void Display::init(GLFWwindow * & win) {
    win = glfwCreateWindow(
            1600,
            900,
            "Plop Engine",
            nullptr,
            nullptr
    );
    if(!win){
        std::cerr << "GLFW : Window or OpenGL Context creation error !" << std::endl;
        return;
    }

    /* Setting the current OpenGL context */
    glfwMakeContextCurrent(win);

    glewExperimental = true; get_error();

    if(glewInit() != GLEW_OK){
        std::cerr << "Glew initialisation error !" << std::endl;
        get_error();
        quit(win);
        return;
    }
    glGetError();

    glEnable(GL_DEPTH_TEST); get_error("enable depth");
    glEnable(GL_CULL_FACE); get_error("enable cull");
    glCullFace(GL_BACK); get_error("cull both");
    glfwSwapInterval(1);
}

void Display::quit(GLFWwindow * win) {
    glfwDestroyWindow(win);
    glfwTerminate();
}

void Display::cls() {
    glClearColor(.4f, .4f, .4f, 1.f); get_error();
    GLbitfield mask = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT;
    glClear(mask); get_error();
}

void Display::frame() {
    glfwSwapBuffers(Engine::engine.data.win);
}

void Display::render_sgv(SGV * sgv) {
    if(sgv) { sgv->render(); }
}