//
// Created by mazrog on 21/12/17.
//

#ifndef ENGINE_GUIBOX_HPP
#define ENGINE_GUIBOX_HPP

#include <gui/gui.hpp>
#include "guiRender.hpp"

class Guibox : public GUI {
public:
    Guibox(std::string const& tag);
    ~Guibox();

    void render() override {
        if( isVisible() ) {
            guiRender(dynamicData);
        }
    }

private:
    GuiRender   guiRender;
};


#endif //ENGINE_GUI_HPP
