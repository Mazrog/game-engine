//
// Created by mazrog on 21/11/17.
//

#ifndef ENGINE_PLANE_HPP
#define ENGINE_PLANE_HPP

#include "scenegraph/sg_logic.hpp"

template < class Render >
class Plane : public SGL_Node {
public:
    Plane(int subx = 0, int suby = 0);

    void render() { renderer( dynamicData ); }

private:
    Render renderer;
};

constexpr int n = 20;
constexpr float dimin = .85f;
constexpr float dimin_stat = -.1f;

constexpr float threshold = 0.f;

using matn = std::array<float, (n+1)*(n+1)>;

void prop(matn & mat, int x, int y, float coef) {
    int ind = x*n+y;
    if(mat[ind] <= threshold || mat[ind] < coef) {
        mat[ind] = coef;
    }
    else { coef = mat[ind]; }

    if(coef >= 1.f) {
        coef = 2*std::log(coef);
    } else {
        coef = coef * ( (coef <= 0) ? 1.f + dimin : dimin ) + dimin_stat;
    }

    coef = roundf(coef * 1000) / 1000;

    if(coef > threshold) {
        if( x > 0 && (mat[ind-n] < coef)) { prop(mat, x - 1, y, coef); }
        if( y > 0 && (mat[ind-1] < coef)) { prop(mat, x, y - 1, coef); }
        if( x < n-1 && (mat[ind+n] < coef)) { prop(mat, x + 1, y, coef); }
        if( y < n-1 && (mat[ind+1] < coef)) { prop(mat, x, y + 1, coef); }
    }

}

void plop(matn & mat) {
    vecord visco;

    visco.emplace_back(n/3 + 1, n-6, 3);
    visco.emplace_back(n/2+2, n/2+1, 1.3);
    visco.emplace_back(3, 4, .5f);

    for(auto const& v : visco) {
        mat[v.x * n + v.y] = v.z;
        prop(mat, (int) v.x, (int) v.y, v.z);
    }
}

template < class Render >
Plane<Render>::Plane(int subx, int suby) {
    renderingData.vertices  = std::make_unique<vecord>();
    renderingData.links     = std::make_unique<vecui>();

    matn plane;
    plane.fill(threshold - .1f);

    plop(plane);

    int n_vertices = (n + 1)*(n + 1);
    float x, z;

    for(int i = 0; i <= n; ++i) {
        z = -.5f + i * (1.f / n);
        for(int j = 0 ; j <= n; ++j) {
            x = -.5f + j * (1.f / n);
            std::cout << plane[i*n+j] << "\t\t";
            renderingData.vertices->emplace_back(x, plane[i*n+j], z);
        }

        std::cout << std::endl;
    }

    for(int i = 0; i < n_vertices; ++i) {
        if( !i || (i % (n + 1) != n) ) {
            renderingData.links->push_back(i);
            renderingData.links->push_back(i + 1);
            renderingData.links->push_back(i + n + 1);

            renderingData.links->push_back(i + 1);
            renderingData.links->push_back(i + n + 1);
            renderingData.links->push_back(i + n + 2);
        }
    }

    glm::vec3 scale(5.f, 1.f, 5.f);

    dynamicData.tranform = std::make_unique<glm::mat4>(
            scale.x, 0, 0, 0,
            0, scale.y, 0, 0,
            0, 0, scale.z, 0,
            0, 0.f, 0, 1.f);


    Render::init();
    renderer = Render(this);
}

#endif //ENGINE_PLANE_HPP
