//
// Created by mazrog on 15/11/17.
//

#ifndef ENGINE_UNIFORM_HPP
#define ENGINE_UNIFORM_HPP

#include <GL/glew.h>

struct Uniform {
    Uniform(GLuint progid, const char * name);

    GLuint progid;
};


#endif //ENGINE_UNIFORM_HPP
