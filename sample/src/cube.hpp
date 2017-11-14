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
    ~Cube();

    void render();

private:
    Render renderer;
};

#include "cube.tpp"

#endif //ENGINE_CUBE_HPP
