#version 430 core

out vec4 color;

in vec2 pass_uvs;

uniform sampler2D terrain_texture;

void main() {
    color = texture(terrain_texture, pass_uvs);
}
