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

    std::vector<GLushort> indices = {
            0, 1, 2, 3, 0, 2, 5, 4, 6, 7, 9, 8, 10, 12, 11, 13, 15, 14  // wypisujemy tyle elementów ile mamy wierzchołków
    };

    std::vector<GLfloat> vertices = {
            1.0f, 0.0f, -1.0f, 0.4, 0.1, 0.2,
            1.0f, 0.0f, 1.0f, 0.4, 0.1, 0.2,
            -1.0f, 0.0f, 1.0f, 0.4, 0.1, 0.2,
            -1.0f, 0.0f, -1.0f, 0.4, 0.1, 0.2,

            1.0f, 0.0f, -1.0f, 0.3, 0.5, 0.6,
            1.0f, 0.0f, 1.0f, 0.3, 0.5, 0.6,
            0.0f, 1.0f, 0.0f, 0.3, 0.5, 0.6,

            1.0f, 0.0f, 1.0f, 0.3, 0.2, 0.3,
            -1.0f, 0.0f, 1.0f, 0.3, 0.2, 0.3,
            0.0f, 1.0f, 0.0f, 0.3, 0.2, 0.3,

            -1.0f, 0.0f, 1.0f, 0.4, 0.4, 0.2,
            -1.0f, 0.0f, -1.0f, 0.4, 0.4, 0.2,
            0.0f, 1.0f, 0.0f, 0.4, 0.4, 0.2,

            -1.0f, 0.0f, -1.0f, 0.2, 0.8, 0.4,
            1.0f, 0.0f, -1.0f, 0.2, 0.8, 0.4,
            0.0f, 1.0f, 0.0f, 0.2, 0.8, 0.4
    };
};

