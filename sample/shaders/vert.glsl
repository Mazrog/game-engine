#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_col;

layout (location = 10) in vec3 in_uvs;

uniform mat4 transform;

out vec3 move_color;
out vec3 move_uvs;

void main() {
    gl_Position = transform * vec4(in_pos, 1.0);

    move_color = in_col;
    move_uvs = in_uvs;
}
