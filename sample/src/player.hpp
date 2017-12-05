//
// Created by mazrog on 04/12/17.
//

#ifndef ENGINE_PLAYER_HPP
#define ENGINE_PLAYER_HPP

#include <scenegraph/sg_logic.hpp>

template < class Render >
class Player : public SGL_Node {
public:
    Player();
    ~Player() = default;


    void render() override { renderer( dynamicData ); }

private:
    Render renderer;
};

template < class Render >
Player<Render>::Player() {
    Loader::load_obj_element("sample/obj/person.obj", model);

    Render::init();
    renderer.setData(this);
}

#endif //ENGINE_PLAYER_HPP
