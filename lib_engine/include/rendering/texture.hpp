//
// Created by mazrog on 22/11/17.
//

#ifndef ENGINE_TEXTURE_HPP
#define ENGINE_TEXTURE_HPP

#include "rendering/structs/uniform.hpp"

struct TextureFormat {
    GLenum       internal_format;
    GLenum       format;
    const char * texturePath;

    TextureFormat(const char * texturePath, GLenum internal_format = GL_RGB, GLenum format = GL_RGB);
};

class Texture {
public:
    Texture(GLenum type = GL_TEXTURE_2D);
    ~Texture();

    Texture& operator=(Texture const&) = delete;

    Texture& operator=(Texture && text);

    void loadImageToVram(const char * image,
                         GLenum internal_format = GL_RGB, GLenum format = GL_RGB);
    void loadUniform(GLuint progID, const char * var_name);

    void bind() const;
    void send(int slot) const;

private:
    Uniform     texture;
    GLenum      type;
    GLuint      id;
};


#endif //ENGINE_TEXTURE_HPP
