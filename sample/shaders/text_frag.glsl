#version 330 core

uniform sampler2D glyph_texture;

in vec2 pass_uvs;

out vec4 color;

void main() {

    color = vec4(1., 1., 1., texture(glyph_texture, pass_uvs).r );
}