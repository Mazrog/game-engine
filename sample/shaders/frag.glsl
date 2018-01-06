#version 330 core


in vec2 pass_uvs;
in vec3 surface_normal;
in vec3 to_light_vector;
in float blend_fog;

uniform sampler2D entity_texture;
uniform vec3 sun_color;

out vec4 color;

void main() {
    vec3 unit_normal = normalize(surface_normal);
    vec3 unit_to_light = normalize(to_light_vector);

    float brightness = dot(unit_normal, unit_to_light);
    /* Ajout d'une lumière ambiante (.2f et non 0) */
    brightness = max(brightness, .2f);

    color = max(texture(entity_texture, pass_uvs), vec4(.1f, .1f, .1f, 1.f)) * (brightness * vec4(sun_color, 1.0));

    color = mix(color, vec4(.007f, .014f, .021f, 1.f), blend_fog);
}
