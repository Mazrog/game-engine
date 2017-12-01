#version 430 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uvs;
layout (location = 2) in vec3 in_normals;

uniform mat4 transform;
uniform mat4 main_camera;
uniform vec3 sun_pos;

out vec2 pass_uvs;
out vec3 pass_normals;
out vec3 to_light_vector;

void main() {
    vec4 tmp = transform * vec4(in_pos, 1.f);

    gl_Position = main_camera * tmp;

    pass_uvs = in_uvs;

    pass_normals = in_normals;

    to_light_vector = sun_pos - tmp.xyz;
}
