#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uvs;

uniform mat4 transform;

out vec2 pass_uvs;

const vec2 quad[6] = vec2[](
    vec2(-.8f, .8f), vec2(0.f, .8f), vec2(0.f, -.8f),
    vec2(0.f, -.8f), vec2(-.8f, -.8f), vec2(-.8f, .8f) );

void main() {
    gl_Position = vec4(in_pos, 1.f);

    pass_uvs = in_uvs;
}
