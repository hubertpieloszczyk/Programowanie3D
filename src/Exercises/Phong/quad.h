//
// Created by huber on 07.01.2021.
//

#pragma once

#include "glad/glad.h"
#include <glm/glm.hpp>
#include <vector>
#include "memory"

class Quad  {
public:
    Quad();
    ~Quad();

    void draw(glm::mat4 &PVM, GLuint u_pvm_buffer_);
    void draw(glm::mat4 &P,glm::mat4 &VM,glm::mat3 &N,GLuint u_pvm_buffer_);

    Quad(const Quad& rhs) = delete;
    Quad &operator=(Quad *rhs) = delete;

    void operator=(Quad&& rhs) = delete;
    Quad(Quad&& rhs) = delete;

    std::shared_ptr<Quad> quad_;

private:
    GLuint vao_{};
    GLuint buffer_[2]{};

    GLuint diffuse_texture_;

    std::vector<GLushort> indices = {
            0, 1, 2, 3, 0, 2 // wypisujemy tyle elementów ile mamy wierzchołków
    };

    std::vector<GLfloat> vertices = {
            1.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
            -1.0f, 0.0f, -1.0f, 0.0, 0.0f, 0.0f, 1.0f, 0.0f,
    };
};

