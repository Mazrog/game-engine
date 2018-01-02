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

    glTexImage2D(type, 0, internal_format,
                 ilGetInteger(IL_IMAGE_WIDTH),
                 ilGetInteger(IL_IMAGE_HEIGHT), 0,
                 format, GL_UNSIGNED_BYTE, surf);
    get_error("tex image 2D");

    ilDeleteImage(src);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

    return ids.size()-1;
}

int Texture::loadCubeMapToVram(const char *folderPath, GLenum internal_format, GLenum format) {
    genTexture();
    bind();

    const char * file_names[6] = { "right.png", "left.png",
                                   "top.png", "bottom.png",
                                   "back.png", "front.png" };

    ilInit();
    ILuint src = ilGenImage();
    ilBindImage(src);

    char image_name[500];

    for(unsigned i = 0; i < 6; ++i) {
        snprintf(image_name, sizeof(image_name), "%s/%s", folderPath, file_names[i]);

        ilLoadImage(image_name);
        ILubyte *surf = ilGetData();

        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internal_format,
                     ilGetInteger(IL_IMAGE_WIDTH),
                     ilGetInteger(IL_IMAGE_HEIGHT), 0,
                     format, GL_UNSIGNED_BYTE, surf);
        get_error("tex image 2D");
    }

    ilDeleteImage(src);

    glTexParameteri(type, GL_TEXTURE_MIN_FILTER, GL_LINEAR); get_error("mipmap linear");
    glTexParameteri(type, GL_TEXTURE_MAG_FILTER, GL_LINEAR); get_error("texture param MAG");

    glTexParameteri(type, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(type, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

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