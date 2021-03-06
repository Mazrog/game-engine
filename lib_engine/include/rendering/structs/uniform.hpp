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
inline void send_uniform<int>(GLint const& loc, int const& f) {
    glUniform1i(loc, f); get_error("send int");
}

template <>
inline void send_uniform<float>(GLint const& loc, float const& f) {
    glUniform1f(loc, f); get_error("send float");
}

template <>
inline void send_uniform<glm::mat4>(GLint const& loc, glm::mat4 const& m) {
    glUniformMatrix4fv(loc, 1, GL_FALSE, glm::value_ptr(m)); get_error("send mat");
}

template <>
inline void send_uniform<glm::vec3>(GLint const& loc, glm::vec3 const& v) {
    glUniform3f(loc, v.x, v.y, v.z); get_error("send vec3");
}

/* ################################################################################## */

struct Uniform {
    Uniform() = default;
    Uniform(GLuint progid, const char * name);

    ~Uniform();

    void loadUniform(GLuint progID, const char * var_name);

    /* ---------- */
    Uniform(Uniform const&) = delete;
    Uniform& operator=(Uniform const&) = delete;

    Uniform(Uniform && unif);
    Uniform& operator=(Uniform && unif);
    /* ------------ */

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
