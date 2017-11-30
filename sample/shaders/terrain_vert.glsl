#version 430 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uvs;
layout (location = 2) in vec3 in_normals;

uniform mat4 transform;
uniform mat4 main_camera;

out vec2 pass_uvs;

void main() {
    vec4 tmp = transform * vec4(in_pos, 1.f);

    gl_Position = main_camera * tmp;

    pass_uvs = in_uvs;
}
