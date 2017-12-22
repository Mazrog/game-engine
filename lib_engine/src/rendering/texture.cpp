//
// Created by mazrog on 22/11/17.
//

#include <IL/il.h>

#include "rendering/texture.hpp"


TextureFormat::TextureFormat(const char * texturePath, GLenum internal_format, GLenum format) :
        internal_format(internal_format), format(format), texturePath(texturePath) {}


Texture::Texture(GLenum type) : type(type) {
    glGenTextures(1, &id);      get_error("Texture generation");
}

Texture::~Texture() {
    if(id) {
        glDeleteTextures(1, &id); get_error("Texture deletion");
    }
}

Texture& Texture::operator=(Texture && text) {
    id = text.id;
    type = text.type;
    texture = std::move(text.texture);

    text.id = 0;
    return *this;
}

void Texture::loadImageToVram(const char *image, GLenum internal_format, GLenum format) {
    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage(image);
    ILubyte * surf = ilGetData();

    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format,
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 format, GL_UNSIGNED_BYTE, surf);
    get_error("tex image 2D");

    ilDeleteImage(src);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");
}

void Texture::bind() const {
    glBindTexture(type, id);        get_error("Texture binding");
}

void Texture::send(int slot) const {
    glActiveTexture(GL_TEXTURE0 + slot);    get_error("Texture active");
    bind();
    texture.send(slot);
}

void Texture::loadUniform(GLuint progID, const char *var_name) {
    texture.loadUniform(progID, var_name);
}