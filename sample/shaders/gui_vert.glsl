#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uvs;

uniform mat4 transform;

out vec2 pass_uvs;


void main() {
    gl_Position = transform * vec4(in_pos, 1.f);

    pass_uvs = in_uvs;
}
