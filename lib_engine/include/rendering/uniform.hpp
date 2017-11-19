//
// Created by mazrog on 15/11/17.
//

#ifndef ENGINE_UNIFORM_HPP
#define ENGINE_UNIFORM_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "rendering/program.hpp"
#include "utils.hpp"

/* Sending function template */
template <typename T>
inline void send_uniform(GLint const& loc, T const&);

template <>
inline void send_uniform<float>(GLint const& loc, float const& f) {
    glUniform1f(loc, f); get_error();
}

template <>
inline void send_uniform<glm::mat4>(GLint const& loc, glm::mat4 const& m) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)); get_error();
}

/* ################################################################################## */

struct Uniform {
    Uniform(GLuint progid, const char * name);

    template < typename T >
    void send(T const& t) const {
        /* Use the correct program */
        ShaderProgram::useProgram(progid);
        send_uniform(location, t);
    }

    GLuint progid;
    GLint  location;
    const char * name;
};


#endif //ENGINE_UNIFORM_HPP
