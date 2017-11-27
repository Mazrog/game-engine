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



    void processVertex3f(std::stringstream & sstr, vecord & vec) {
        float x, y, z;

        sstr >> x >> y >> z;
        vec.emplace_back(x, y, z);
    }

    void processVertex2f(std::stringstream & sstr, vecuvs & vec) {
        float x, y;

        sstr >> x >> y;
        vec.emplace_back(x, y);
    }

    void processFace(std::stringstream & sstr, Model & model) {
        std::cout << sstr.str() << std::endl;
        int v1[3], v2[3], v3[3];

        for(int i = 0; i < 3; ++i) {
            std::string tmp;
            std::getline(sstr, tmp, '/');
            v1[i] = std::atoi(tmp.c_str());
        }

    }

    void load_obj(const char * obj_file, Model & model) {
        std::ifstream file(obj_file);
        std::string line, word;

        if(file) {

            do {
                line.clear();
                std::getline(file, line, '\n');

                if(!line.empty()) {
                    std::stringstream sstr(line);
                    sstr >> word;
                    switch (line[0]) {
                        case 'v':
                            switch (line[1]) {
                                case 't':
                                    processVertex2f(sstr, model.uvs);
                                    break;
                                case 'n':
                                    processVertex3f(sstr, model.normals);
                                    break;
                                default:
                                    processVertex3f(sstr, model.vertices);
                                    break;
                            }
                            break;
                        case 'f':
                            processFace(sstr, model);
                            break;
                        default:;
                    }
                }
            } while(!file.eof());

            for(auto const& v : model.vertices) {
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
            }

            for(auto const& v : model.uvs) {
                std::cout << v.x << " " << v.y << std::endl;
            }

            for(auto const& v : model.normals) {
                std::cout << v.x << " " << v.y << " " << v.z << std::endl;
            }

        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }
}