//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Terrain : public SGL_Node {
public:
    Terrain(int length = 20, int width = 20);

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};


template < class Render >
Terrain<Render>::Terrain(int length, int width) {

    int n_vertices = length*width;
    float x, z;

    for(int i = 0; i < width; ++i) {
        z = -.5f + i * (1.f / width);
        for(int j = 0 ; j < length; ++j) {
            x = -.5f + j * (1.f / length);
            model.vertices.emplace_back(x, 0.f, z);
        }

//        std::cout << std::endl;
    }

    for(int i = 0; i < n_vertices; ++i) {
        if( !i || (i % length  != (length - 1)) ) {
            model.links.push_back(i);
            model.links.push_back(i + 1);
            model.links.push_back(i + length);

            model.links.push_back(i + 1);
            model.links.push_back(i + length);
            model.links.push_back(i + length + 1);
        }
        model.normals.emplace_back(0.f, 1.f, 0.f);
    }

    glm::vec3 scale(5.f, 1.f, 5.f);

    dynamicData.tranform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0.f, 0, 1.f
    );


    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_PLANE_HPP
