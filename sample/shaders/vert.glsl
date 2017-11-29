#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec2 in_uv;
layout (location = 2) in vec3 in_normal;

uniform mat4 transform;
uniform mat4 main_camera;
uniform vec3 main_camera_pos;

/* Sun uniforms */
uniform vec3 sun_pos;


out vec2 pass_uvs;
out vec3 surface_normal;
out vec3 to_light_vector;

void main() {
    vec4 world_position = transform * vec4(in_pos, 1.0);

    gl_Position = main_camera * world_position;

    surface_normal = (transform * vec4(in_normal, 0.f)).xyz;
    to_light_vector = sun_pos - world_position.xyz;

    pass_uvs = in_uv;
}
