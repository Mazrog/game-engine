#version 330 core

in vec3 move_color;

out vec4 color;

void main() {
    color = vec4(move_color, 1.0);
}
