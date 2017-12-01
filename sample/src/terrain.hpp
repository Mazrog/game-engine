//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <IL/il.h>

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Terrain : public SGL_Node {
public:
    static constexpr int SIZE         = 150;
    static constexpr int MAX_COLOR    = 255 + 255 + 255;
    static constexpr int MAX_HEIGHT   = 40;

public:
    Terrain(const char * pathheightmap = nullptr,
            glm::vec3 const& position = glm::vec3(0.f));

    void render() { renderer( dynamicData ); }

    float get_height(int x, int z, ILubyte * heightmap);

    glm::vec3 calculate_normal(int x, int z, ILubyte * heightmap);

private:
    Render renderer;
};

template < class Render >
float Terrain<Render>::get_height(int x, int z, ILubyte * heightmap) {
    ILuint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    ILuint width = ilGetInteger(IL_IMAGE_WIDTH);

    if(x < 0 || z < 0) { return 0; }

    ILubyte * pixel = heightmap + z * width * bpp + x * bpp;

    float val = (Uint8) *pixel + (Uint8) *(pixel+1) + (Uint8) *(pixel+2);

    val = (val * MAX_HEIGHT) / (float) MAX_COLOR;

    return val;
}

template < class Render >
glm::vec3 Terrain<Render>::calculate_normal(int x, int z, ILubyte * heightmap) {
    float heightL = get_height(x-1, z, heightmap);
    float heightR = get_height(x+1, z, heightmap);
    float heightD = get_height(x, z-1, heightmap);
    float heightU = get_height(x, z+1, heightmap);
    glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);

    return glm::normalize(normal);
}

template < class Render >
Terrain<Render>::Terrain(const char * pathheightmap,
                         glm::vec3 const& position) {

    ilInit();

    ilLoadImage(pathheightmap);

    ILubyte * heightmap = ilGetData();

    ILuint VERT_COUNT = ilGetInteger(IL_IMAGE_WIDTH);

    glm::vec3 tmp;
    for(unsigned i = 0; i < VERT_COUNT; ++i) {
        for(unsigned j = 0; j < VERT_COUNT; ++j) {
            tmp.x = (float) j / ((float) VERT_COUNT - 1) * SIZE;
            tmp.y = get_height(j, i, heightmap);
            tmp.z = (float) i / ((float) VERT_COUNT - 1) * SIZE;

            model.vertices.emplace_back(tmp.x, tmp.y, tmp.z);

            tmp = calculate_normal(j, i, heightmap);

            model.normals.emplace_back(tmp.x, tmp.y, tmp.z);

            tmp.x = (float) j / ((float) VERT_COUNT - 1);
            tmp.y = (float) i / ((float) VERT_COUNT - 1);
            model.uvs.emplace_back(tmp.x, tmp.y);
        }
    }

    for (unsigned gz = 0; gz < VERT_COUNT - 1; gz++) {
        for (unsigned gx = 0; gx < VERT_COUNT - 1; gx++) {
            int topLeft = (gz * VERT_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERT_COUNT) + gx;
            int bottomRight = bottomLeft + 1;

            model.links.push_back(topLeft);
            model.links.push_back(bottomLeft);
            model.links.push_back(topRight);

            model.links.push_back(topRight);
            model.links.push_back(bottomLeft);
            model.links.push_back(bottomRight);
        }
    }

    ilClearImage();


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
