#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_col;

uniform mat4 transform;

uniform mat4 viewpoint_camera;

out vec3 move_color;


void main() {
    gl_Position = viewpoint_camera * transform * vec4(in_pos, 1.0);

    move_color = in_col;
}
