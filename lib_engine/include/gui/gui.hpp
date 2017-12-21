//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUI_HPP
#define ENGINE_GUI_HPP

#include <string>
#include "rendering/model.hpp"

class GUI {
public:
    GUI(std::string const& tag);
    virtual ~GUI();

    virtual void show();
    virtual void hide();
    virtual void toggle();

    virtual void render();

    /* Getters */
    Model * get_model() { return model; }

    bool isVisible() const { return visible; }

public:
    std::string     tag;

protected:
    bool              visible;

    Model           * model;
    DynamicData       dynamicData;
};


#endif //ENGINE_GUI_HPP
