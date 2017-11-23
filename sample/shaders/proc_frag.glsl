#version 330 core

in float pos_y;

out vec4 color;

const float y_max = 2.f;
const float y_min = -1.f;

float abs(float f) {
    return ( f < 0 ) ? -f : f;
}

vec3 make_color(float y) {
    vec3 col = vec3(.3f, .3f, 0.f);

    vec3 p_min = vec3(0.62f, 0.81f, .44f);
    vec3 p_max = vec3(0.39f, 0.16f, 0.f);

    vec3 n_min = vec3(0.2f, 0.69f, .66f);
    vec3 n_max = vec3(0.2f, 0.41f, 0.69f);

    if(y > 0) {
        col = (y / y_max) * p_min + (1.f - y/y_max) * p_max;
    } else {
        col = (y / y_min) * n_max + (1.f - y/y_min) * n_min;
    }

    return col;
}

void main() {
    color = vec4(make_color(pos_y), 1.0);
}
