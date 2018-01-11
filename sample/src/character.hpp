//
// Created by mazrog on 04/12/17.
//

#ifndef ENGINE_CHARACTER_HPP
#define ENGINE_CHARACTER_HPP

#include "terrain.hpp"
#include "rendering/renderer/renderEntity.hpp"

class Character : public SGL_Node {
public:
    Character(const char * model, Terrain * terrain);
    ~Character() = default;

    void move() override;

    void render() override { renderer( dynamicData ); }

private:
    RenderEntity      renderer;
    Terrain         * terrain;

    /* Game related */
private:

};

#endif //ENGINE_PLAYER_HPP
