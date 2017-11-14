//
// Created by mazrog on 12/11/17.
//

/* remove this include, just for dev ide */
#include "cube.hpp"

template < class Render >
Cube< Render >::Cube() {
    /* temporaire, prévoir chargement OBJ */
    renderingData.vertices.emplace_back(-0.5, 0.5, 0.5);
    renderingData.vertices.emplace_back(0.5, 0.5, 0.5);
    renderingData.vertices.emplace_back(0.5, -0.5, 0.5);
    renderingData.vertices.emplace_back(-0.5, -0.5, 0.5);
    renderingData.vertices.emplace_back(-0.5, -0.5, -0.5);
    renderingData.vertices.emplace_back(-0.5, 0.5, -0.5);
    renderingData.vertices.emplace_back(0.5, 0.5, -0.5);
    renderingData.vertices.emplace_back(0.5, -0.5, -0.5);

    renderingData.uvs.emplace_back(0.0, 0.0, 0.0);
    renderingData.uvs.emplace_back(0.0, 1.0, 0.0);
    renderingData.uvs.emplace_back(1.0, 1.0, 0.0);
    renderingData.uvs.emplace_back(1.0, 0.0, 0.0);
    renderingData.uvs.emplace_back(1.0, 1.0, 0.0);
    renderingData.uvs.emplace_back(1.0, 0.0, 0.0);
    renderingData.uvs.emplace_back(0.0, 0.0, 0.0);
    renderingData.uvs.emplace_back(0.0, 1.0, 0.0);

    int linking[] = {
            0, 1, 2, 2, 3, 0, //Face avant
            6, 5, 4, 4, 7, 6, //Face arrière
            5, 6, 1, 1, 0, 5, //Face haut
            6, 7, 2, 2, 1, 6, //Face droite
            3, 2, 7, 7, 4, 3, //Face bas
            0, 3, 4, 4, 5, 0 //Face gauche
    };

    for(unsigned i = 0; i < 36; ++i){
        renderingData.links.push_back(linking[i]);
    }

    Render::init();
    renderer = Render(this);
}

template < class Render >
Cube<Render>::~Cube() = default;

template < class Render >
void Cube<Render>::render() {
    Render()();
}