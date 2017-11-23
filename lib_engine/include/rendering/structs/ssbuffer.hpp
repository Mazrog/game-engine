//
// Created by mazrog on 23/11/17.
//

#ifndef ENGINE_SSBUFFER_HPP
#define ENGINE_SSBUFFER_HPP

#include <GL/glew.h>

#include "utils.hpp"

class SSBuffer {
public:
    SSBuffer();
    ~SSBuffer();


    template < class T >
    void map_data(T const * data, unsigned long size,
                  GLbitfield mask = GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT) {
        glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo); get_error("binding map data");
        glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(T) * size, nullptr, GL_STATIC_DRAW); get_error("buffer storage data");

        T* vert = static_cast<T*>(glMapBufferRange(GL_SHADER_STORAGE_BUFFER,
                                                 0,
                                                 sizeof(T) * size,
                                                 mask));
        get_error("map buffer");

        for(unsigned i = 0; i < size; ++i) {
            vert[i] = data[i];
        }

        glUnmapBuffer(GL_SHADER_STORAGE_BUFFER); get_error("unmap ssbo");
    }

    GLuint get_id() const { return ssbo; }

private:
    GLuint      ssbo;
};


#endif //ENGINE_SSBUFFER_HPP
