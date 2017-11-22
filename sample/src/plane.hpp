//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Plane : public SGL_Node {
public:
    Plane();

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Plane<Render>::Plane() {
    renderingData.vertices = std::make_unique<vecord>();

    /* LEFT TOP */
    renderingData.vertices->emplace_back(-.5f, 0.f, -.5f);
    renderingData.vertices->emplace_back(1.f, .3f, 0.f);

    /* RIGHT TOP */
    renderingData.vertices->emplace_back(.5f, 0.f, -.5f);
    renderingData.vertices->emplace_back(.3f, .5f, 0.f);

    /* RIGHT BOTTOM */
    renderingData.vertices->emplace_back(.5f, .0f, .5f);
    renderingData.vertices->emplace_back(0.f, .4f, .3f);

    /* RIGHT BOTTOM */
    renderingData.vertices->emplace_back(.5f, .0f, .5f);
    renderingData.vertices->emplace_back(0.f, .4f, .3f);

    /* LEFT BOTTOM */
    renderingData.vertices->emplace_back(-.5f, .0f, .5f);
    renderingData.vertices->emplace_back(0.f, .4f, .3f);

    /* LEFT TOP */
    renderingData.vertices->emplace_back(-.5f, 0.f, -.5f);
    renderingData.vertices->emplace_back(1.f, .3f, 0.f);

    glm::vec3 scale(15.f);

    dynamicData.tranform = std::make_unique<glm::mat4>(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0.f, 0, 1.f);


    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_PLANE_HPP
