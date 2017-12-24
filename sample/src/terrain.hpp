//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include <IL/il.h>

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Terrain : public SGL_Node {
public:
    static constexpr int SIZE         = 300;
    static constexpr int MAX_COLOR    = 255 + 255 + 255;
    static constexpr int MAX_HEIGHT   = 40;

public:
    Terrain(const char * pathheightmap = nullptr,
            glm::vec3 const& position = glm::vec3(0.f));

    ~Terrain();

    void render() override { renderer( dynamicData ); }

    float get_height(unsigned x, unsigned z, ILubyte * heightmap);
    glm::vec3 calculate_normal(int x, int z, ILubyte * heightmap);

private:
    Render renderer;

    float      * heights;
};

template < class Render >
float Terrain<Render>::get_height(unsigned x, unsigned z, ILubyte * heightmap) {
    ILuint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    ILuint width = ilGetInteger(IL_IMAGE_WIDTH);

    if(x < 0 || x >= width || z < 0 || z >= width) { return 0; }

    ILubyte * pixel = heightmap + x * width * bpp + z * bpp;

    float val = (uint8_t) *pixel + (uint8_t) *(pixel+1) + (uint8_t) *(pixel+2);
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

    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage(pathheightmap);
    ILubyte * heightmap = ilGetData();
    ILuint VERT_COUNT = ilGetInteger(IL_IMAGE_WIDTH);

    heights = new float[VERT_COUNT*VERT_COUNT];

    glm::vec3 tmp;
    for(unsigned i = 0; i < VERT_COUNT; ++i) {
        for(unsigned j = 0; j < VERT_COUNT; ++j) {
            tmp.x = (float) j / ((float) VERT_COUNT - 1) * SIZE;
            tmp.z = (float) i / ((float) VERT_COUNT - 1) * SIZE;
            float height = get_height(j, i, heightmap);
            tmp.y = height;
            heights[i*VERT_COUNT + j] = height;

            model->vertices.emplace_back(tmp.x, tmp.y, tmp.z);

            tmp = calculate_normal(j, i, heightmap);

            model->normals.emplace_back(tmp.x, tmp.y, tmp.z);

            tmp.x = (float) j / ((float) VERT_COUNT - 1);
            tmp.y = (float) i / ((float) VERT_COUNT - 1);
            model->uvs.emplace_back(tmp.x, tmp.y);
        }
    }

    for (unsigned gz = 0; gz < VERT_COUNT - 1; gz++) {
        for (unsigned gx = 0; gx < VERT_COUNT - 1; gx++) {
            int topLeft = (gz * VERT_COUNT) + gx;
            int topRight = topLeft + 1;
            int bottomLeft = ((gz + 1) * VERT_COUNT) + gx;
            int bottomRight = bottomLeft + 1;

            model->links.push_back(topLeft);
            model->links.push_back(bottomLeft);
            model->links.push_back(topRight);

            model->links.push_back(topRight);
            model->links.push_back(bottomLeft);
            model->links.push_back(bottomRight);
        }
    }

    ilDeleteImage(src);


    glm::vec3 scale(1.f);

    dynamicData.transform = glm::mat4(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            -SIZE/2.f + position.x, position.y, -SIZE/2.f + position.z, 1.f
    );


    Render::init();
    renderer.setData(this);
}

template < class Render >
Terrain<Render>::~Terrain() {
    std::cout << "delete terrain" << std::endl;
    delete [] heights;
    renderer.clean();
}

#endif //ENGINE_PLANE_HPP
