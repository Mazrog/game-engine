#version 330 core


in vec3 pass_uvs;
in vec3 surface_normal;
in vec3 to_light_vector;


uniform sampler2D textCube;
uniform vec3 sun_color;

out vec4 color;

void main() {

    vec3 unit_normal = normalize(surface_normal);
    vec3 unit_to_light = normalize(to_light_vector);

    float brightness = dot(unit_normal, unit_to_light);
    /* Ajout d'une lumière ambiante (.2f et non 0) */
    brightness = max(brightness, .2f);

    color = texture(textCube, pass_uvs.xy) + (brightness * vec4(sun_color, 0.0));
}
