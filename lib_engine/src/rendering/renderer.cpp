//
// Created by mazrog on 12/11/17.
//

#include "rendering/renderer.hpp"

Renderer::RenderConfig::RenderConfig() :
        primitive(GL_TRIANGLES),
        count(0),
        is_element(false) {}