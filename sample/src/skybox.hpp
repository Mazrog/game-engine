//
// Created by mazrog on 01/01/18.
//

#ifndef ENGINE_SKYBOX_HPP
#define ENGINE_SKYBOX_HPP

#include <scenegraph/sg_logic.hpp>
#include "skyboxRender.hpp"

class Skybox : public SGL_Node {
public:
    Skybox(std::string const& tag, const char * texturepath);
    ~Skybox() = default;

    void render() override;

private:
    SkyboxRender renderer;
};


#endif //ENGINE_SKYBOX_HPP
