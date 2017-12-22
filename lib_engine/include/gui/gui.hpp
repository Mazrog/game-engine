//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUI_HPP
#define ENGINE_GUI_HPP

#include <string>
#include "rendering/model.hpp"
#include "rendering/texture.hpp"

#include <freetype2/ft2build.h>

struct GuiData {
    std::wstring text;

    GuiData(std::wstring const& t = L"Default phrase...") : text(t) {}
};

class GUI {
public:
    GUI(std::string const& tag,
        const char * texturePath,
        GLenum internal_format = GL_RGB,
        GLenum format = GL_RGB);
    virtual ~GUI();

    virtual void show();
    virtual void hide();
    virtual void toggle();

    virtual void render();

    /* Getters */
    Model * get_model() { return model; }

    bool isVisible() const { return visible; }
    TextureFormat const& get_textureFormat() const { return textureFormat; }

public:
    std::string     tag;

protected:
    bool              visible;

    Model           * model;
    DynamicData       dynamicData;

    TextureFormat     textureFormat;

    GuiData           guiData;
};


#endif //ENGINE_GUI_HPP
