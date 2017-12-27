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

    void genTexture();

    int loadImageToVram(const char * image,
                         GLenum internal_format = GL_RGB, GLenum format = GL_RGB);
    void loadUniform(GLuint progID, const char * var_name);

    void bind() const;
    void bind(GLuint index) const;
    void send(int index, int slot = 0) const;

    bool isActive() const { return !ids.empty(); }

private:
    Uniform                 texture;
    GLenum                  type;
    std::vector<GLuint>     ids;
};


#endif //ENGINE_TEXTURE_HPP
