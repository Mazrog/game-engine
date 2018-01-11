//
// Created by mazrog on 11/01/18.
//

#ifndef ENGINE_ENTITY_HPP
#define ENGINE_ENTITY_HPP

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer/renderEntity.hpp"

class Entity : public SGL_Node {
public:
    Entity(const char * model,
           glm::vec3 position = glm::vec3(0.f),
           glm::vec3 rotation = glm::vec3(0.f),
           glm::vec3 scale = glm::vec3(1.f));
    ~Entity() {}

    void render() override {
        renderer( dynamicData );
    }

private:
    RenderEntity      renderer;
};


#endif //ENGINE_ENTITY_HPP
