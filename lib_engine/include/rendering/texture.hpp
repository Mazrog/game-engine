//
// Created by mazrog on 22/11/17.
//

#ifndef ENGINE_TEXTURE_HPP
#define ENGINE_TEXTURE_HPP

#include "rendering/structs/uniform.hpp"

class Texture {
public:
    Texture(GLenum type = GL_TEXTURE_2D);
    ~Texture();

    Texture& operator=(Texture const&) = delete;

    Texture& operator=(Texture && text);

    void loadImageToVram(const char * image);
    void loadUniform(GLuint progID, const char * var_name);

    void bind() const;
    void send(int slot) const;

private:
    Uniform     texture;
    GLenum      type;
    GLuint      id;
};


#endif //ENGINE_TEXTURE_HPP
