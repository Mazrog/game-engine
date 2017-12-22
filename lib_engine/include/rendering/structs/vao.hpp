//
// Created by mazrog on 03/12/17.
//

#ifndef ENGINE_VAO_HPP
#define ENGINE_VAO_HPP

#include <vector>

#include "vbo.hpp"
#include "utils.hpp"

class Vao {
public:
    Vao();
    ~Vao();

    Vao(Vao const&) = delete;
    Vao& operator=(Vao const &) = delete;

    Vao(Vao && vao);
    Vao& operator=(Vao && vao);

    void bind();
    void clean();


    template < class T >
    void linkDataAttribute(GLuint index, int coordinateSize, size_t size, T * data) {
        bind();
        vbos.emplace_back();
        if( size ) {
            vbos.back().setBufferData(size, data);
        }

        glEnableVertexAttribArray(index);   get_error("VAO enable vertex index");
        glVertexAttribPointer(index, coordinateSize, GL_FLOAT, GL_FALSE, 0, (void *) 0);    get_error("VAO vertex pointer");
    }

    template < class T >
    void linkElementDataAttribute(size_t size, T * data) {
        bind();
        vbos.emplace_back(GL_ELEMENT_ARRAY_BUFFER);
        vbos.back().setBufferData(size, data);
    }


    /* Getters */
    GLuint getId() const { return id; }
    std::vector<Vbo> getVbos() { return vbos; }

    /* Setters */
    void setId(GLuint new_id) { id = new_id; }

private:
    GLuint                  id;
    std::vector<Vbo>      vbos;
};


#endif //ENGINE_VAO_HPP
