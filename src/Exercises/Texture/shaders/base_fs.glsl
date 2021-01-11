#version 410

in vec2 texture_coords;
uniform sampler2D diffuse_map;

layout(location=0) out vec4 vFragColor;

void main() {
    vFragColor = texture(diffuse_map, texture_coords);
}
