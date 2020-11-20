#version 410

in vec3 vertex_color;

layout(location=0) out vec4 vFragColor;

void main() {
    vFragColor.rgb = vertex_color;
    vFragColor.a = 1.0;
}