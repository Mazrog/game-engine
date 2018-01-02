//
// Created by mazrog on 01/01/18.
//

#include "skybox.hpp"

Skybox::Skybox(std::string const &, const char *) : SGL_Node(42) {
    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);

    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);

    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);

    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);

    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(1.0f,  1.0f, -1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f,  1.0f);
    model->vertices.emplace_back(-1.0f,  1.0f, -1.0f);

    model->vertices.emplace_back(-1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(1.0f, -1.0f, -1.0f);
    model->vertices.emplace_back(-1.0f, -1.0f,  1.0f);
    model->vertices.emplace_back(1.0f, -1.0f,  1.0f);

    dynamicData.scale = glm::vec3(500.f);
    dynamicData.update();

    renderer.setData(this);
}

void Skybox::render() {
    renderer( dynamicData );
}