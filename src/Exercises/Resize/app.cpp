//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Application/utils.h"

void SimpleShapeApplication::init() {


    auto program = xe::create_program(std::string(PROJECT_DIR) + "/shaders/base_vs.glsl",
                                      std::string(PROJECT_DIR) + "/shaders/base_fs.glsl");


    if (!program) {
        std::cerr << "Cannot create program from " << std::string(PROJECT_DIR) + "/shaders/base_vs.glsl" << " and ";
        std::cerr << std::string(PROJECT_DIR) + "/shaders/base_fs.glsl" << " shader files" << std::endl;
    }

    auto u_modifiers_index = glGetUniformBlockIndex(program, "Modifiers");
    if (u_modifiers_index == GL_INVALID_INDEX)
    {
        std::cout << "Cannot find Modifiers uniform block in program" << std::endl;
    }
    else
    {
        glUniformBlockBinding(program, u_modifiers_index, 1);
    }

    std::vector<GLushort> indices = {
            0, 2, 1, 0, 3, 2, 5, 6, 4, 9, 8, 7, 11, 10, 12, 13, 14, 15  // wypisujemy tyle elementów ile mamy wierzchołków
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

    float strength = 1.2;
    float light[3] = {1.0, 1.2, 1.4};

    GLuint ubo_handle(0u);
    glGenBuffers(1,&ubo_handle);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle);
    glBufferData(GL_UNIFORM_BUFFER, 8 * sizeof(float), nullptr, GL_STATIC_DRAW);

    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(float),&strength);
    glBufferSubData(GL_UNIFORM_BUFFER, 4 * sizeof(float), 3 * sizeof(float),light);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 1, ubo_handle);

    GLuint v_buffer_handle;
    glGenBuffers(1, &v_buffer_handle);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint idx_buffer_handle;
    glGenBuffers(1,&idx_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLushort), indices.data(),
                 GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glBindBuffer(GL_ARRAY_BUFFER, v_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idx_buffer_handle);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(0));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<GLvoid *>(3 * sizeof(GLfloat)));
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    int w, h;
    std::tie(w, h) = frame_buffer_size();

    glm::mat4 M(1.0f);
    auto V = glm::lookAt(glm::vec3{-0.5,1.0,2.0},glm::vec3{-0.5,-0.5,-0.5},glm::vec3{0.0,1.0,1.0});
    auto P = glm::perspective(glm::half_pi<float>(),(float)w/h,0.1f,100.0f);
    glm::mat4 PVM = P * V * M;

    GLuint ubo_handle_pvm(0u);
    glGenBuffers(1, &ubo_handle_pvm);
    glBindBuffer(GL_UNIFORM_BUFFER, ubo_handle_pvm);
    glBufferData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 1);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, ubo_handle_pvm);

    auto u_transformations_index = glGetUniformBlockIndex(program, "Transformations");
    if (u_transformations_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Transformations uniform block in program" << std::endl;
    } else {
        glUniformBlockBinding(program, u_transformations_index, 0);
    }

    std::tie(w, h) = frame_buffer_size();
    aspect_ = (float)w/h;
    fov_ = glm::pi<float>()/4.0;
    near_ = 0.1f;
    far_ = 100.0f;
    P_ = glm::perspective(fov_, aspect_, near_, far_);
    V_ = glm::lookAt(glm::vec3{-0.5,1.0,2.0},glm::vec3{-0.5,-0.5,-0.5},glm::vec3{0.0,1.0,1.0});

    glGenBuffers(1, &u_pvm_buffer_);
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferData(GL_UNIFORM_BUFFER,2*sizeof(glm::mat4), nullptr, GL_STATIC_DRAW);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer_);

    glViewport(0, 0, w, h);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    glCullFace(GL_BACK);

    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    auto PVM = P_ * V_;
    glBindBuffer(GL_UNIFORM_BUFFER, u_pvm_buffer_);
    glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(glm::mat4), &PVM[0]);
    glBindBuffer(GL_UNIFORM_BUFFER, 0);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, u_pvm_buffer_);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, nullptr);
    glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    aspect_ = (float) w / h;
    P_ = glm::perspective(fov_, aspect_, near_, far_);
}
