//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_CUBE_HPP
#define ENGINE_CUBE_HPP

#include <vector>

#include "scenegraph/sg_logic.hpp"
#include "utils.hpp"

template < class Render >
class Cube : public SGL_Node {
public:
    Cube();
    ~Cube() = default;

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Cube< Render >::Cube() {
    Loader::load_obj("sample/obj/suzanneHybrid.obj", model);

    glm::vec3 scale(2.f);

    dynamicData.tranform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 1.f, 0, 1.f);

    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_CUBE_HPP
