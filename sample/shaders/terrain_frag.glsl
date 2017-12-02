#version 430 core

out vec4 color;

in vec2 pass_uvs;
in vec3 pass_normals;
in vec3 to_light_vector;

uniform sampler2D terrain_texture;

void main() {
//    color = texture(terrain_texture, pass_uvs);
//    color = vec4(.3, .7, .1, 1.);

    vec3 unitNormal = normalize(pass_normals);
    vec3 unitToLight = normalize(to_light_vector);

    float brightness = dot(unitNormal, unitToLight);
    brightness = max(brightness, 0.2f);

//    color = vec4(.2f, .7f, .4f, 1.f) * (brightness * vec4(.788f, .886f, 1.f, 1.f));
    color = max(texture(terrain_texture, pass_uvs), .2f) * (brightness * vec4(.788f, .886f, 1.f, 1.f));
}
