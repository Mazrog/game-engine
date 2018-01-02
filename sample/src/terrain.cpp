//
// Created by mazrog on 29/12/17.
//

#include "terrain.hpp"

float Terrain::get_height(unsigned x, unsigned z, ILubyte * heightmap) {
    ILuint bpp = ilGetInteger(IL_IMAGE_BYTES_PER_PIXEL);
    ILuint width = ilGetInteger(IL_IMAGE_WIDTH);

    if(x >= width || z >= width) { return 0; }

    ILubyte * pixel = heightmap + x * width * bpp + z * bpp;

    float val = (uint8_t) *pixel + (uint8_t) *(pixel+1) + (uint8_t) *(pixel+2);
    val = (val * MAX_HEIGHT) / (float) MAX_COLOR;

    return val;
}

glm::vec3 Terrain::calculate_normal(int x, int z, ILubyte * heightmap) {
    float heightL = get_height(x-1, z, heightmap);
    float heightR = get_height(x+1, z, heightmap);
    float heightD = get_height(x, z-1, heightmap);
    float heightU = get_height(x, z+1, heightmap);
    glm::vec3 normal(heightL - heightR, 2.f, heightD - heightU);

    return glm::normalize(normal);
}


float Terrain::get_height(float worldX, float worldZ) {
    glm::vec2 gridPos = (glm::vec2(worldX, worldZ) + SIZE / 2.f) / resolution;

    glm::ivec2 ipos = glm::ivec2(gridPos);

    return (ipos.x < 0 || ipos.x > SIZE || ipos.y < 0 || ipos.y > SIZE) ? 0.f :
           heights.at(ipos.y).at(ipos.x) + .2f;
}

Terrain::Terrain(const char * pathheightmap,
                 glm::vec3 const& position) {
    ilInit();

    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage(pathheightmap);
    ILubyte * heightmap = ilGetData();
    ILuint VERT_COUNT = ilGetInteger(IL_IMAGE_WIDTH);

    resolution = SIZE / (float) VERT_COUNT;

    glm::vec3 tmp;
    for(unsigned i = 0; i < VERT_COUNT; ++i) {
        heights.emplace_back();
        for(unsigned j = 0; j < VERT_COUNT; ++j) {
            tmp.x = (float) j / ((float) VERT_COUNT - 1) * SIZE;
            tmp.z = (float) i / ((float) VERT_COUNT - 1) * SIZE;
            float height = get_height(j, i, heightmap);
            tmp.y = height;
            heights.at(i).push_back(height);

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

    renderer.setData(this);
}

Terrain::~Terrain() {
    heights.clear();
    renderer.clean();
}