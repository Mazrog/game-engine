//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Terrain : public SGL_Node {
public:
    Terrain(int width, int length, glm::vec3 const& position = glm::vec3(0.f));

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};


template < class Render >
Terrain<Render>::Terrain(int width, int length, glm::vec3 const& position) {
    model.vertices.emplace_back(-length/2.f, 0.f, -width/2.f);
    model.vertices.emplace_back( length/2.f, 0.f, -width/2.f);
    model.vertices.emplace_back( length/2.f, 0.f,  width/2.f);
    model.vertices.emplace_back(-length/2.f, 0.f,  width/2.f);

    model.uvs.emplace_back(0, 0);
    model.uvs.emplace_back(1, 0);
    model.uvs.emplace_back(1, 1);
    model.uvs.emplace_back(0, 1);

    model.normals.emplace_back(0, 1.f, 0);
    model.normals.emplace_back(0, 1.f, 0);
    model.normals.emplace_back(0, 1.f, 0);
    model.normals.emplace_back(0, 1.f, 0);

    GLuint links[] = {
            0, 1, 2,
            2, 3, 0
    };

    for(int i = 0; i < 6; ++i) {
        model.links.emplace_back(links[i]);
    }

    glm::vec3 scale(1.f);

    dynamicData.tranform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            position.x, position.y, position.z, 1.f
    );


    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_PLANE_HPP
