//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUI_HPP
#define ENGINE_GUI_HPP

#include <string>
#include <vector>
#include <freetype2/ft2build.h>

#include "rendering/model.hpp"
#include "rendering/texture.hpp"
#include "guiData.hpp"

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
    virtual void build_guiData();

    virtual void render();

    virtual void spread_visibility();

    void add(GUI * child);

    /* DEBUG FUNCTIONS */
    void debug() const;

    /* Getters */
    Model * get_model() { return model; }
    Point const& get_anchor() const { return guiData.anchor; }
    Dimension const& get_dimension() const { return guiData.dimension; }
    Dimension const& get_content_dimension() const { return guiData.contentDimension; }

    bool isVisible() const { return visible; }
    TextureFormat const& get_textureFormat() const { return textureFormat; }

    /* Setters */
    void set_anchor(Point const& point) { guiData.anchor = point; }
    void set_visibility(bool visibility) { visible = visibility; }
    void set_dimension(Dimension const& dim) { guiData.dimension = dim; }
    void set_content_dimension(Dimension const& dim) { guiData.contentDimension = dim; }

public:
    std::string         tag;
    std::vector<GUI *>  children;

protected:
    bool              visible;

    Model           * model;
    DynamicData       dynamicData;
    TextureFormat     textureFormat;
    GuiData           guiData;
};


#endif //ENGINE_GUI_HPP
