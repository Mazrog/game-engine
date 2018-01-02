#version 330 core

in vec3 pass_uvs;
in float y_pos;

out vec4 color;

uniform samplerCube skybox_texture;

void main() {
    vec4 skybox = texture(skybox_texture, pass_uvs);

    float blend = smoothstep(50.f, 400.f, y_pos);

    color = mix(skybox, vec4(.01f, .02f, .03f, 1.f), 1 - blend);
}
