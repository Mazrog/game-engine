//
// Created by mazrog on 12/11/17.
//

#ifndef ENGINE_CUBE_HPP
#define ENGINE_CUBE_HPP

#include <vector>

#include "scenegraph/sg_logic.hpp"

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
    /* temporaire, prévoir chargement OBJ */
    model.vertices.emplace_back(-0.5, 0.5, 0.5);
    model.vertices.emplace_back(0.5, 0.5, 0.5);
    model.vertices.emplace_back(0.5, -0.5, 0.5);
    model.vertices.emplace_back(-0.5, -0.5, 0.5);
    model.vertices.emplace_back(-0.5, -0.5, -0.5);
    model.vertices.emplace_back(-0.5, 0.5, -0.5);
    model.vertices.emplace_back(0.5, 0.5, -0.5);
    model.vertices.emplace_back(0.5, -0.5, -0.5);

    model.uvs.emplace_back(0.0, 0.0);
    model.uvs.emplace_back(0.0, 1.0);
    model.uvs.emplace_back(1.0, 1.0);
    model.uvs.emplace_back(1.0, 0.0);
    model.uvs.emplace_back(1.0, 1.0);
    model.uvs.emplace_back(1.0, 0.0);
    model.uvs.emplace_back(0.0, 0.0);
    model.uvs.emplace_back(0.0, 1.0);

    model.normals.emplace_back(0.0, 0.0, 1.0);
    model.normals.emplace_back(0.0, 0.0, 1.0);
    model.normals.emplace_back(0.0, 0.0, 1.0);
    model.normals.emplace_back(0.0, 0.0, 1.0);
    model.normals.emplace_back(0.0, 0.0, -1.0);
    model.normals.emplace_back(0.0, 0.0, -1.0);
    model.normals.emplace_back(0.0, 0.0, -1.0);
    model.normals.emplace_back(0.0, 0.0, -1.0);

    int linking[] = {
            0, 1, 2, 2, 3, 0, //Face avant
            6, 5, 4, 4, 7, 6, //Face arrière
            5, 6, 1, 1, 0, 5, //Face haut
            6, 7, 2, 2, 1, 6, //Face droite
            3, 2, 7, 7, 4, 3, //Face bas
            0, 3, 4, 4, 5, 0 //Face gauche
    };

    for(unsigned i = 0; i < 36; ++i){
        model.links.push_back(linking[i]);
    }

    glm::vec3 scale(1.f);

    dynamicData.tranform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, -2.f, 0, 1.f);

    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_CUBE_HPP
