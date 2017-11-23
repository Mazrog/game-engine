#version 330 core

layout (location = 0) in vec3 in_pos;

uniform mat4 transform;

uniform mat4 viewpoint_camera;

out float pos_y;


void main() {
    vec4 tmp = transform * vec4(in_pos, 1.0);

    gl_Position = viewpoint_camera * tmp;

    pos_y = tmp.y;
}
