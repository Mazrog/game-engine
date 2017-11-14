#version 330 core

layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_col;

out vec3 move_color;

void main() {
    gl_Position = vec4(in_pos, 1.0);

    if(in_col != vec3(0.0)){
        move_color = in_col;
    } else {
        move_color = vec3(0.3, 0.0, 0.0);
    }
}
