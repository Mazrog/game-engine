//
// Created by mazrog on 23/11/17.
//

#include <iostream>
#include "utils.hpp"
#include "rendering/structs/ssbuffer.hpp"

SSBuffer::SSBuffer() {
    glGenBuffers(1, &ssbo);                         get_error("gen ssbuffer");
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, ssbo);   get_error("bind ssbuffer");
}

SSBuffer::~SSBuffer() {
    std::cout << "delete ssbo" << std::endl;
}

