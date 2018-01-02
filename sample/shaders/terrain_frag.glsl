#version 430 core

out vec4 color;

in vec2 pass_uvs;
in vec3 pass_normals;
in vec3 to_light_vector;
in float blend_fog;

uniform sampler2D terrain_texture;

void main() {
    vec3 unitNormal = normalize(pass_normals);
    vec3 unitToLight = normalize(to_light_vector);

    float brightness = dot(unitNormal, unitToLight);
    brightness = max(brightness, 0.2f);

    color = max(texture(terrain_texture, pass_uvs), .2f) * (brightness * vec4(.788f, .886f, 1.f, 1.f));
    color = mix(color, vec4(.007f, .014f, .021f, 1.f), blend_fog);
}
