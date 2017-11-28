//
// Created by mazrog on 19/11/17.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>

#include "utils.hpp"

void get_error(const char * t){
    GLenum err;
    if((err = glGetError()) != GLEW_OK){
        std::cerr << t << std::endl;
        std::cerr << "Erreur OpenGL (" << err << ") : " << glewGetErrorString(err) << " -- " << gluErrorString(err) << std::endl;
    }
}

namespace Loader {
    using vert_vec = std::vector<Vertex>;

    void processVertex(std::istringstream & sstr, vert_vec & v_list) {
        float x, y, z;

        sstr >> x >> y >> z;
        v_list.emplace_back(v_list.size(), glm::vec3(x, y, z));
    }

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

    void processVertLink(glm::ivec3 & vec, Model & model, vert_vec & v_list) {
        int index = vec.x - 1;
        Vertex & vertex = v_list.at(index);
        int texture = vec.y - 1;
        int normal = vec.z - 1;

        if( vertex.isSet() ) {
            if( vertex.hasSameIndices(texture, normal) ) {
                model.links.push_back(std::move(index));
            } else {
                Vertex duplicateVertex(v_list.size(), vertex.position);

                duplicateVertex.texture_index = texture;
                duplicateVertex.normal_index = normal;

                v_list.emplace_back(duplicateVertex);
                model.links.push_back(std::move(duplicateVertex.vertex_index));
            }
        } else {
            vertex.texture_index = texture;
            vertex.normal_index = normal;
            model.links.push_back(std::move(index));
        }
    }

    void processFace(std::istringstream & sstr, Model & model, vert_vec & v_list) {
        glm::ivec3  v1, v2, v3;
        std::string s1, s2, s3;
        sstr >> s1 >> s2 >> s3;

        parseVec(s1, v1);
        parseVec(s2, v2);
        parseVec(s3, v3);

        processVertLink(v1, model, v_list);
        processVertLink(v2, model, v_list);
        processVertLink(v3, model, v_list);
    }

    void load_obj(const char * obj_file, Model & model) {
        std::ifstream file(obj_file);
        std::string line, word;

        if(file) {

            std::vector<Vertex> vertices;
            vecord normals;
            vecuvs uvs;

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
                                    processVertex(sstr, vertices);
                                    break;
                            }
                            break;
                        case 'f':
                            processFace(sstr, model, vertices);
                            break;
                        default:;
                    }
                }
            } while(!file.eof());


            for(unsigned i = 0; i < vertices.size(); ++i) {
                Vertex vx = vertices.at(i);
                model.vertices.emplace_back(vx.position);
                model.uvs.emplace_back(uvs.at(vx.texture_index));
                model.normals.emplace_back(normals.at(vx.normal_index));
            }


            for(auto const& v : model.vertices) {
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
            }

            for(auto const& v : model.uvs) {
                std::cout << v.x << " " << v.y << std::endl;
            }

            for(auto const& v : model.normals) {
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
            }

            for(auto const& v : model.links) {
                std::cout << v << " # ";
            }
            std::cout << std::endl;

        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }
}