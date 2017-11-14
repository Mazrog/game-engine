//
// Created by mazrog on 14/11/17.
//

#ifndef ENGINE_TRIANGLE_HPP
#define ENGINE_TRIANGLE_HPP


#include "scenegraph/sg_logic.hpp"

template < class Render >
class Triangle : public SGL_Node {
public:
    Triangle();

    void render() { renderer(); }

private:
    Render renderer;
};

template < class Render >
Triangle<Render>::Triangle() {
    renderingData.vertices.emplace_back(-.5f, 0.f, 0.f);
    renderingData.vertices.emplace_back(1.f, .3f, 0.f);

    renderingData.vertices.emplace_back(0.f, .5f, 0.f);
    renderingData.vertices.emplace_back(.3f, .5f, 0.f);

    renderingData.vertices.emplace_back(.5f, 0.f, 0.f);
    renderingData.vertices.emplace_back(0.f, .4f, .3f);

    renderingData.links.push_back(0);
    renderingData.links.push_back(1);
    renderingData.links.push_back(2);

    Render::init();
    renderer = Render(this);
}


#endif //ENGINE_TRIANGLE_HPP
