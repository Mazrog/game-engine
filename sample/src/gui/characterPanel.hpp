//
// Created by mazrog on 28/12/17.
//

#ifndef ENGINE_CHARACTERPANEL_HPP
#define ENGINE_CHARACTERPANEL_HPP


#include <scenegraph/sg_logic.hpp>
#include <gui/elements/guibox.hpp>
#include <gui/elements/textblock.hpp>

class CharacterPanel : public Guibox {
public:
    CharacterPanel(SGL_Node * character);
    ~CharacterPanel();

    void build_guiData() override;
    void render() override;

private:
    SGL_Node                    * character;
};


#endif //ENGINE_CHARACTERPANEL_HPP
