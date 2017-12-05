//
// Created by mazrog on 03/12/17.
//

#ifndef ENGINE_VBO_HPP
#define ENGINE_VBO_HPP

#include <GL/glew.h>
#include "utils.hpp"

class Vbo {
public:
    Vbo(GLenum type = GL_ARRAY_BUFFER);
    ~Vbo();

    void bind();

    void clean();

    template < class T >
    void setBufferData(size_t size, const T * data, GLenum usage = GL_STATIC_DRAW) {
        bind();
        glBufferData(type, size, data, usage);      get_error("VBO Buffer Data");
    }


    GLuint getId() const { return id; }

private:
    GLuint      id;
    GLenum      type;
};


#endif //ENGINE_VBO_HPP
