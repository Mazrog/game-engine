//
// Created by mazrog on 19/11/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <algorithm>

#include "utils.hpp"

void get_error(const char * t){
    GLenum err;
    if((err = glGetError()) != GLEW_OK){
        std::cerr << t << std::endl;
        std::cerr << "Erreur OpenGL (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << std::endl;
    }
}

namespace Loader {
    using vert_map = std::map<Vertex, unsigned>;


    void processVertex3f(std::istringstream & sstr, vecord & vec) {
        float x, y, z;

        sstr >> x >> y >> z;
        vec.emplace_back(x, y, z);
    }

    void processVertex2f(std::istringstream & sstr, vecuvs & vec) {
        float x, y;

        sstr >> x >> y;
        vec.emplace_back(x, y);
    }

    void parseVec(std::string & str, glm::ivec3 & vec) {
        std::string tmp;
        std::istringstream ssvert(str);

        for(int i = 0; i < 3; ++i) {
            tmp.clear();
            std::getline(ssvert, tmp, '/');
            vec[i] = std::atoi(tmp.c_str());
        }
    }

    void processVertLink(glm::ivec3 & vec, Model & model, vert_map & vmap) {
        Vertex cur(vec.x - 1, vec.y - 1, vec.z - 1);

        unsigned & val = vmap[cur];
        unsigned ind;

        if( !val ) {
            /* New Vertex */
            val = vmap.size();
        }
        ind = val;
        model.links.push_back(ind - 1);
    }

    void processFace(std::istringstream & sstr, Model & model, vert_map & vmap) {
        glm::ivec3  v1, v2, v3;
        std::string s1, s2, s3;
        sstr >> s1 >> s2 >> s3;

        parseVec(s1, v1);
        parseVec(s2, v2);
        parseVec(s3, v3);

        processVertLink(v1, model, vmap);
        processVertLink(v2, model, vmap);
        processVertLink(v3, model, vmap);
    }

    void load_obj(const char * obj_file, Model & model) {
        std::ifstream file(obj_file);
        std::string line, word;

        if(file) {

            vecord vertices;
            vecord normals;
            vecuvs uvs;
            vert_map vmap;

            do {
                line.clear();
                std::getline(file, line, '\n');

                if(!line.empty()) {
                    std::istringstream sstr(line);
                    sstr >> word;

                    switch (line[0]) {
                        case 'v':
                            switch (line[1]) {
                                case 't':
                                    processVertex2f(sstr, uvs);
                                    break;
                                case 'n':
                                     processVertex3f(sstr, normals);
                                    break;
                                default:
                                    processVertex3f(sstr, vertices);
                                    break;
                            }
                            break;
                        case 'f':
                            processFace(sstr, model, vmap);
                            break;
                        default:;
                    }
                }
            } while(!file.eof());

            /* Total number of vertices */
            int size = *std::max_element(model.links.begin(), model.links.end()) + 1;

            /* Allocation of the vectors */
            model.vertices.resize(size);
            model.uvs.resize(size);
            model.normals.resize(size);

            /* Filling up with the map information */
            for(auto const& pair : vmap) {
                unsigned indice = pair.second - 1;
                model.vertices[indice] = vertices.at(pair.first.vertex_index);
                if(pair.first.texture_index >= 0) {
                    model.uvs[indice] = uvs.at(pair.first.texture_index);
                }
                if(pair.first.normal_index >= 0) {
                    model.normals[indice] = normals.at(pair.first.normal_index);
                }
            }

        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }
}