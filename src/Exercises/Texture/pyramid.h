//
// Created by huber on 07.01.2021.
//

#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>

class Pyramid  {
public:
    Pyramid();
    ~Pyramid();
    void draw(glm::mat4 &PVM, GLuint u_pvm_buffer_);

    Pyramid(const Pyramid& rhs) = delete;
    Pyramid &operator=(Pyramid *rhs) = delete;

    void operator=(Pyramid&& rhs) = delete;
    Pyramid(Pyramid&& rhs) = delete;

private:
    GLuint vao_{};
    GLuint buffer_[2]{};

    GLuint diffuse_texture_;

    std::vector<GLushort> indices = {
            0, 1, 2, 3, 0, 2, 1, 0, 4, 1, 5, 2, 2, 6, 3, 3, 7, 0  // wypisujemy tyle elementów ile mamy wierzchołków
    };

    std::vector<GLfloat> vertices = {
            1.0f, 0.0f, -1.0f, 0.5,0.191,
            1.0f, 0.0f, 1.0f, 0.809, 0.5,
            -1.0f, 0.0f, 1.0f, 0.5, 0.809,
            -1.0f, 0.0f, -1.0f, 0.191, 0.5,

            0.0f, 1.0f, 0.0f, 1.0, 0.0,
            0.0f, 1.0f, 0.0f, 1.0, 1.0,
            0.0f, 1.0f, 0.0f, 0.0, 1.0,
            0.0f, 1.0f, 0.0f, 0.0, 0.0,
    };
};

