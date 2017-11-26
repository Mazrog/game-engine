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
    void load_obj(const char * obj_file, vecord & vertices, vecuvs & uvs, vecord & normals, vecui & links) {
        std::ifstream file(obj_file);
        std::string line;

        if(file) {




        } else {
            std::cerr << "Error : Could not open OBJ file " << obj_file << std::endl;
        }
    }
}