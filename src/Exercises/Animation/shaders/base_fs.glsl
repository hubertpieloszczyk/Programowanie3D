#version 410

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;


void main() {
    vFragColor.a = 1.0;
    vFragColor.rgb = vertex_color.rgb;
}