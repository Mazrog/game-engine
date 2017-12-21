#version 330 core

uniform sampler2D gui_texture;

in vec2 pass_uvs;

out vec4 color;

void main() {
    color = texture(gui_texture, pass_uvs);
//    color = vec4(1.f, 0.f, 0.f, 1.f);
}
