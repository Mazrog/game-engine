//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Plane : public SGL_Node {
public:
    Plane(int subx = 0, int suby = 0);

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Plane<Render>::Plane(int subx, int suby) {
    renderingData.vertices  = std::make_unique<vecord>();
    renderingData.links     = std::make_unique<vecui>();

    int n_grid = 10;
    int n_vertices = (n_grid + 1)*(n_grid + 1);
    float x, z;

    for(int i = 0; i <= n_grid; ++i) {
        z = -.5f + i * (1.f / n_grid);
        for(int j = 0 ; j <= n_grid; ++j) {
            x = -.5f + j * (1.f / n_grid);
            renderingData.vertices->emplace_back(x, 0.f, z);
        }
    }

    for(int i = 0; i < n_vertices; ++i) {
        if( !i || (i % (n_grid + 1) != n_grid) ) {
            renderingData.links->push_back(i);
            renderingData.links->push_back(i + 1);
            renderingData.links->push_back(i + n_grid + 1);

            renderingData.links->push_back(i + 1);
            renderingData.links->push_back(i + n_grid + 1);
            renderingData.links->push_back(i + n_grid + 2);
        }
    }

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
