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
    renderingData.normals->emplace_back(0.0, 0.0, 1.0);
    renderingData.normals->emplace_back(0.0, 1.0, 0.0);
    renderingData.normals->emplace_back(-1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, 1.0);
    renderingData.normals->emplace_back(0.0, 1.0, 0.0);
    renderingData.normals->emplace_back(1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, 1.0);
    renderingData.normals->emplace_back(0.0, -1.0, 0.0);
    renderingData.normals->emplace_back(1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, 1.0);
    renderingData.normals->emplace_back(0.0, -1.0, 0.0);
    renderingData.normals->emplace_back(-1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, -1.0);
    renderingData.normals->emplace_back(0.0, -1.0, 0.0);
    renderingData.normals->emplace_back(-1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, -1.0);
    renderingData.normals->emplace_back(0.0, 1.0, 0.0);
    renderingData.normals->emplace_back(-1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, -1.0);
    renderingData.normals->emplace_back(0.0, 1.0, 0.0);
    renderingData.normals->emplace_back(1.0, 0.0, 0.0);

    renderingData.normals->emplace_back(0.0, 0.0, -1.0);
    renderingData.normals->emplace_back(0.0, -1.0, 0.0);
    renderingData.normals->emplace_back(1.0, 0.0, 0.0);

    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 1.0);
    renderingData.uvs->emplace_back(0.0, 1.0);
    renderingData.uvs->emplace_back(0.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 1.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(1.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 0.0);
    renderingData.uvs->emplace_back(0.0, 1.0);
    renderingData.uvs->emplace_back(0.0, 1.0);
    renderingData.uvs->emplace_back(0.0, 1.0);

    renderingData.vertices->emplace_back(-0.5, 0.5, 0.5); // Face avant     0
    renderingData.vertices->emplace_back(-0.5, 0.5, 0.5); // Face haut      1
    renderingData.vertices->emplace_back(-0.5, 0.5, 0.5); // Face gauche    2

    renderingData.vertices->emplace_back(0.5, 0.5, 0.5); // Face avant      3
    renderingData.vertices->emplace_back(0.5, 0.5, 0.5); // Face haut       4
    renderingData.vertices->emplace_back(0.5, 0.5, 0.5); // Face droite     5

    renderingData.vertices->emplace_back(0.5, -0.5, 0.5); // Face avant     6
    renderingData.vertices->emplace_back(0.5, -0.5, 0.5); // Face dessous   7
    renderingData.vertices->emplace_back(0.5, -0.5, 0.5); // Face droite    8

    renderingData.vertices->emplace_back(-0.5, -0.5, 0.5); // Face avant    9
    renderingData.vertices->emplace_back(-0.5, -0.5, 0.5); // Face dessous  10
    renderingData.vertices->emplace_back(-0.5, -0.5, 0.5); // Face gauche   11

    renderingData.vertices->emplace_back(-0.5, -0.5, -0.5); // Face arrière 12
    renderingData.vertices->emplace_back(-0.5, -0.5, -0.5); // Face dessous 13
    renderingData.vertices->emplace_back(-0.5, -0.5, -0.5); // Face gauche  14

    renderingData.vertices->emplace_back(-0.5, 0.5, -0.5); // Face arrière  15
    renderingData.vertices->emplace_back(-0.5, 0.5, -0.5); // Face haut     16
    renderingData.vertices->emplace_back(-0.5, 0.5, -0.5); // Face gauche   17

    renderingData.vertices->emplace_back(0.5, 0.5, -0.5); // Face arrière   18
    renderingData.vertices->emplace_back(0.5, 0.5, -0.5); // Face haut      19
    renderingData.vertices->emplace_back(0.5, 0.5, -0.5); // Face droite    20

    renderingData.vertices->emplace_back(0.5, -0.5, -0.5); // Face arrière  21
    renderingData.vertices->emplace_back(0.5, -0.5, -0.5); // Face dessous  22
    renderingData.vertices->emplace_back(0.5, -0.5, -0.5); // Face droite   23

    int linking[] = {
            0, 3, 6, 6, 9, 0, //Face avant
            12, 15, 18, 18, 21, 12, //Face arrière
            1, 4, 16, 16, 19, 1, //Face haut

            5, 8, 20, 20, 23, 8, //Face droite
            7, 10, 13, 13, 22, 7, //Face bas
            2, 11, 14, 14, 17, 2 //Face gauche
    };

    for(unsigned i = 0; i < 36; ++i){
        renderingData.links->push_back(linking[i]);
    }

    glm::vec3 scale(1.f);

    dynamicData.tranform = std::make_unique<glm::mat4>(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, -2.f, 0, 1.f);

    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_CUBE_HPP
