//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PROCEDURAL_HPP
#define ENGINE_PROCEDURAL_HPP

#include <GL/glew.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer.hpp"
#include "rendering/structs/uniform.hpp"

class TerrainRenderer : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    TerrainRenderer();
    explicit TerrainRenderer(SGL_Node * node);

    ~TerrainRenderer() = default;

    void operator()( DynamicData const& dd ) override;

private:
    GLuint          vao;
    GLuint          vbos[4];

    Uniform         transform;
};


#endif //ENGINE_PROCEDURAL_HPP
