//
// Created by mazrog on 22/11/17.
//

#include <IL/il.h>

#include "rendering/texture.hpp"


TextureFormat::TextureFormat(const char * texturePath, GLenum internal_format, GLenum format) :
        internal_format(internal_format), format(format), texturePath(texturePath) {}


Texture::Texture(GLenum type) : type(type) {}

Texture::~Texture() {
    for(auto const& id : ids) {
        if (id) {
            glDeleteTextures(1, &id);
            get_error("Texture deletion");
        }
    }
}

Texture& Texture::operator=(Texture && text) {
    ids = std::move(text.ids);
    type = text.type;
    texture = std::move(text.texture);

    text.ids.clear();
    return *this;
}

void Texture::genTexture() {
    ids.push_back(0);
    glGenTextures(1, &ids.back());      get_error("Texture generation");
}

int Texture::loadImageToVram(const char *image, GLenum internal_format, GLenum format) {
    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);
    ilLoadImage(image);
    ILubyte * surf = ilGetData();

    genTexture();
    bind();

    glTexImage2D(GL_TEXTURE_2D, 0, internal_format,
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 format, GL_UNSIGNED_BYTE, surf);
    get_error("tex image 2D");

    ilDeleteImage(src);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

    return ids.size()-1;
}

void Texture::bind() const {
    bind(ids.size()-1);
}

void Texture::bind(GLuint index) const {
    glBindTexture(type, ids.at(index)); get_error("Texture binding");
}

void Texture::send(int index, int slot) const {
    bind(index);
    glActiveTexture(GL_TEXTURE0 + slot);    get_error("Texture active");
    texture.send(slot);
}

void Texture::loadUniform(GLuint progID, const char *var_name) {
    texture.loadUniform(progID, var_name);
}