#version 330 core

layout (location = 0) in vec4 in_vert;

out vec2 pass_uvs;

uniform mat4 transform;

void main() {
    gl_Position = vec4(in_vert.xy, 0.f, 1.f);

    pass_uvs = in_vert.zw;
}
