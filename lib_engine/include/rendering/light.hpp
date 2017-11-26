//
// Created by mazrog on 26/11/17.
//

#ifndef ENGINE_LIGHT_HPP
#define ENGINE_LIGHT_HPP

#include <GL/glew.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/structs/uniform.hpp"

struct Uniform_light {
    Uniform_light(cref<GLuint> id1, const char * name1,
                  cref<GLuint> id2, const char * name2) :
            light_pos(id1, name1), light_color(id2, name2) {}

    Uniform light_pos;
    Uniform light_color;

    void send(crvec3 pos, crvec3 color) const {
        light_pos.send(pos);
        light_color.send(color);
    }
};

class Light : public SGL_Node {
public:
    Light(crvec3 pos, crvec3 color, const char * name = "sun");

    /* Sending all the uniforms to the programs */
    void render();

    void update() {};

    /* Binding function */
    template < typename ...>
    void bind_light() {}

    template < typename ... Ps >
    void bind_light(GLuint const& progId, Ps const&... progs) {
        vec_uniforms.emplace_back(
                progId, (std::string(name) + std::string("_pos")).c_str(),
                progId, (std::string(name) + std::string("_color")).c_str()
        );
        bind_light(progs...);
    }
    /* ########################################## */

    /* ------------------------------------------- */
private:
    glm::vec3 pos;
    glm::vec3 color;

    const char * name;
    bool         updated;

    std::vector<Uniform_light>    vec_uniforms;
};


#endif //ENGINE_LIGHT_HPP
