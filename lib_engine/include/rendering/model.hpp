//
// Created by mazrog on 18/12/17.
//

#ifndef ENGINE_MODEL_HPP
#define ENGINE_MODEL_HPP

#include "scenegraph/scenegraph.hpp"

using VertInfo = std::pair<unsigned, unsigned>;

struct Material {
    glm::vec3   ka;
    glm::vec3   kd;
    glm::vec3   ks;

    std::string map_Ka;
    std::string map_Kd;
    std::string map_Ks;

    int     map_indexes[3];

    std::vector<VertInfo> vert_infos;
};

using MtlLib = std::map<std::string, Material *>;

struct Model {
    Model();
    Model(const char * file);
    ~Model();
    void clear();


    vecf    vertices;
    vec2f   uvs;
    vecf    normals;
    vecui   links;

    MtlLib  mtlLib;
};


#endif //ENGINE_MODEL_HPP
