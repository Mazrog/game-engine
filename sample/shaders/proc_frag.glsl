#version 330 core

in float pos_y;

uniform float y_max;

out vec4 color;

float abs(float f) {
    return ( f < 0 ) ? -f : f;
}

void main() {
    color = vec4(.3f, .3f, 0.f, 1.0);
}
