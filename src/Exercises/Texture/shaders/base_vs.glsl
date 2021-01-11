#version 410

layout(location=0) in vec4 a_vertex_position;
layout(location=1) in vec2 a_vertex_texture;

layout(std140) uniform Transformations {
    mat4 PVM;
};

out vec2 texture_coords;

void main() {
    gl_Position = PVM * a_vertex_position;
    texture_coords = a_vertex_texture;
}