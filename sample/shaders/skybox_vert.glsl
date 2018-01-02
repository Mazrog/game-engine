#version 330 core

layout ( location = 0 ) in vec3 in_pos;

uniform mat4 transform;
uniform mat4 main_camera;
uniform vec3 main_camera_pos;

out vec3 pass_uvs;
out float y_pos;

void main() {
    vec4 world_position = transform * vec4(in_pos, 1.f);
    gl_Position = main_camera * world_position;

    pass_uvs = in_pos;
    y_pos = world_position.y;
}
