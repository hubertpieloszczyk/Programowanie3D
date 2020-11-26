#version 410

in vec3 vertex_color;
layout(location=0) out vec4 vFragColor;

layout(std140) uniform Modifiers {
    float  strength;
    vec3   light;
};

void main() {
    vFragColor.rgb = strength * light * vertex_color.rgb;
}