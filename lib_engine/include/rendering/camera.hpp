//
// Created by mazrog on 13/11/17.
//

#ifndef ENGINE_CAMERA_HPP
#define ENGINE_CAMERA_HPP

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "rendering/structs/uniform.hpp"
#include "scenegraph/sg_logic.hpp"
#include "utils.hpp"

enum CAM_DIR : unsigned short {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

struct Uniform_camera {
    Uniform_camera(cref<GLuint> id1, const char * name1,
                  cref<GLuint> id2, const char * name2) :
            camera_pos(id1, name1), camera_viewpoint(id2, name2) {}

    Uniform camera_pos;
    Uniform camera_viewpoint;

    void send(crvec3 pos, cref<glm::mat4> viewpoint) const {
        camera_pos.send(pos);
        camera_viewpoint.send(viewpoint);
    }
};

class Camera : public SGL_Node {
public:
    Camera(const char * name = "main_camera");
    Camera(crvec3 pos, crvec3 aim = glm::vec3(0), crvec3 up = glm::vec3(0, 1.f, 0), const char * name = "main_camera");

    /* Build characteristics */
    void init();

    void set_carac(cref<float> angle_rad = 55.f,
                   cref<float> ratio = 16.f / 9.f,
                   cref<float> near = 0.1f,
                   cref<float> far = 1000.f);

    /* Sending all the uniforms to the programs */
    void render();

    /* Update position */
    void update();
    void center_on();
    void follow(SGL_Node * target_elem);

    /* Events management */
    void move() override ;

    /* Binding function */
    template < typename ...>
    void bind_camera() {}

    template < typename ... Ps >
    void bind_camera(GLuint const& progId, Ps const&... progs) {
        vec_uniform.emplace_back(
                progId, (std::string(name) + std::string("_pos")).c_str(),
                progId, name
        );
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
    bool         updated;

    glm::mat4 perspective;
    glm::mat4 cam_mat;

    /* Vector of uniform saving the camera data for each program */
    std::vector<Uniform_camera>    vec_uniform;

    /* Angles */
    float   d_yaw;
    float   d_pitch;
    float   d_roll;

    /* Speeds */
    float    move_speed;
    float    look_speed;

    /* Target and following options */
    SGL_Node    * target;
    float         dist_from_target;
};


#endif //ENGINE_CAMERA_HPP
