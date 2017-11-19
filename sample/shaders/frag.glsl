#version 330 core

uniform sampler2D textCube;

in vec3 move_color;
in vec3 move_uvs;

out vec4 color;

void main() {
    if(move_color != vec3(0.0)){
        color = vec4(move_color, 1.0);
    } else {
        color = texture(textCube, move_uvs.xy) + vec4(.1f, .1f, .1f, 1f);
    }
}
