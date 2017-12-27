#version 330 core

uniform sampler2D   glyph_texture;
uniform vec3        font_color;

in vec2 pass_uvs;

out vec4 color;

void main() {
    vec3 f_color = vec3(1.f);

    color = vec4(1., 1., 1., texture(glyph_texture, pass_uvs).r )
            * vec4(f_color, 1.f);
}
