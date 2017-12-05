//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PROCEDURAL_HPP
#define ENGINE_PROCEDURAL_HPP

#include <GL/glew.h>

#include "scenegraph/sg_logic.hpp"
#include "rendering/renderer.hpp"
#include "rendering/structs/uniform.hpp"
#include "rendering/structs/vao.hpp"
#include "rendering/texture.hpp"

class TerrainRenderer : public Renderer {
public:
    static void init();
    static ShaderProgram    prog;

public:
    TerrainRenderer();
    ~TerrainRenderer();

    void clean() override {};

    void setData(SGL_Node * node);

    /* No copy constructor */
    TerrainRenderer(TerrainRenderer const&) = delete;
    TerrainRenderer& operator=(TerrainRenderer const&) = delete;

    /* But move ones */
    TerrainRenderer(TerrainRenderer &&) = delete;
    TerrainRenderer& operator=(TerrainRenderer && tr);

    void operator()( DynamicData const& dd ) override;

private:
    Vao     vao;

    Uniform         transform;
    Texture         texture;
};


#endif //ENGINE_PROCEDURAL_HPP
