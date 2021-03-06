//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include <IL/il.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer/renderEntity.hpp"

class GameState;

using FloatGrid = std::vector<std::vector<float>>;

class Terrain : public SGL_Node {
public:
    /* Some values passed as arguments to constructor ? */
    static constexpr int SIZE         = 1000;
    static constexpr int MAX_COLOR    = 255 + 255 + 255;
    static constexpr int MAX_HEIGHT   = 40;

public:
    Terrain(const char * pathheightmap = nullptr,
            glm::vec3 const& position = glm::vec3(0.f));

    ~Terrain();

    void load_terrain_from_file(const char * file, GameState * state);

    void render() override { renderer( dynamicData ); }

    float get_height(unsigned x, unsigned z, ILubyte * heightmap);
    glm::vec3 calculate_normal(int x, int z, ILubyte * heightmap);

    float get_height(float worldX, float worldZ);

private:
    RenderEntity renderer;
    float           resolution;

    FloatGrid heights;
};

#endif //ENGINE_PLANE_HPP
