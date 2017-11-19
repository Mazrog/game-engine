//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "rendering/uniform.hpp"
#include "scenegraph/sg_logic.hpp"
#include "utils.hpp"

enum CAM_DIR : unsigned short {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

class Camera : public SGL_Node {
public:
    Camera(const char * name = "viewpoint_camera");
    Camera(crvec3 pos, crvec3 aim, crvec3 up, const char * name = "viewpoint_camera");

    /* Build characteristics */
    void init();

    void set_carac(cref<float> angle_rad = 55.f,
                   cref<float> ratio = 12.f / 9.f,
                   cref<float> near = 0.1f,
                   cref<float> far = 1000.f);

    /* Sending all the uniforms to the programs */
    void render();

    /* Binding function */
    template < typename ...>
    void bind_camera() {}

    template < typename ... Ps >
    void bind_camera(GLuint const& progId, Ps const&... progs) {
        vec_uniform.emplace_back(progId, name);
        bind_camera(progs...);
    }
    /* ########################################## */

    /* Move functions */
    void move_forward();
    void move_backward();

    void move_aim(cref<short> direction);

    /* ------------------------------------------- */
private:
    glm::vec3 pos;
    glm::vec3 aim;
    glm::vec3 up;

    const char * name;

    glm::mat4 perspective;

    /* Vector of uniform saving the camera data for each program */
    std::vector<Uniform>    vec_uniform;

    /* Angles */
    float   yaw;
    float   pitch;
    float   roll;

    /* Speeds */
    float    move_speed;
    float    look_speed;
};


#endif //ENGINE_CAMERA_HPP
