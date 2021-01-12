//
// Created by pbialas on 25.09.2020.
//

#include "app.h"

#include <iostream>
#include <vector>
#include <tuple>
#include <glm/gtx/string_cast.hpp>

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

    set_camera(new Camera);
    set_controler(new CameraControler(camera()));

    glClearColor(0.81f, 0.81f, 0.8f, 1.0f);

    pyramid_ = std::make_shared<Pyramid>();

    int w, h;
    std::tie(w, h) = frame_buffer_size();


    auto u_transformations_index = glGetUniformBlockIndex(program, "Transformations");
    if (u_transformations_index == GL_INVALID_INDEX) {
        std::cout << "Cannot find Transformations uniform block in program" << std::endl;
    } else {
        glUniformBlockBinding(program, u_transformations_index, 0);
    }

    camera_->perspective(glm::pi<float>()/4.0, (float)w/h, 0.1f, 100.0f);
    camera_->look_at(glm::vec3{0.0,40.0,0.0},glm::vec3{0.0,0.0,0.0},glm::vec3{0.0,1.0,1.0});


    start_ = std::chrono::steady_clock::now();
    rotation_period = 4.0;

    glViewport(0, 0, w, h);
    glEnable(GL_DEPTH_TEST);
    glUseProgram(program);
}

void SimpleShapeApplication::frame() {
    int a = 10;
    int b = 8;
    auto now = std::chrono::steady_clock::now();
    auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<float>>(now - start_).count();
    auto rotation_angle = 2.0f*glm::pi<float>()*elapsed_time/rotation_period;
    auto R = glm::rotate(glm::mat4(1.0f), rotation_angle,glm::vec3({0,1,0}));
    auto orbital_rotation_period = 20.0f;
    auto orbital_rotation_angle = 2.0f*glm::pi<float>()*elapsed_time/orbital_rotation_period;
    auto x = a*sin(orbital_rotation_angle);
    auto z = b*cos(orbital_rotation_angle);
    auto O = glm::translate(glm::mat4(1.0f), glm::vec3{x,0.0,z});
    auto M = camera_->projection()*camera_->view()*O*R;

    pyramid_->draw(M, u_pvm_buffer_);

    auto moon_orbital_rotation_angle = 2.0f*glm::pi<float>()*elapsed_time/10.0f;
    auto x_moon = 3.0f*cos(moon_orbital_rotation_angle);
    auto z_moon = 3.0f*sin(moon_orbital_rotation_angle);
    auto R_moon = glm::rotate(glm::mat4(1.0f), moon_orbital_rotation_angle, glm::vec3{0, 1, 0});
    auto O_moon = glm::translate(glm::mat4(1.0f), glm::vec3{x_moon,0.0,z_moon});
    auto S_moon = glm::scale(glm::mat4(1.0f), glm::vec3{0.5f, 0.5f, 0.5f});
    auto PVM_moon = camera_->projection() * camera_->view() * O * O_moon * R_moon * S_moon;

    pyramid_->draw(PVM_moon, u_pvm_buffer_);

    auto satellite_orbital_rotation_angle = 2.0f*glm::pi<float>()*elapsed_time/2.0f;
    auto x_satellite = 1.5f*cos(satellite_orbital_rotation_angle);
    auto y_satellite = 1.5f*sin(satellite_orbital_rotation_angle);
    auto R_satellite = glm::rotate(glm::mat4(1.0f), satellite_orbital_rotation_angle, glm::vec3{0, 0, 1});
    auto O_satellite = glm::translate(glm::mat4(1.0f), glm::vec3{x_satellite,y_satellite,0.0});
    auto S_satellite = glm::scale(glm::mat4(1.0f), glm::vec3{0.25f, 0.25f, 0.25f});
    auto PVM_satellite = camera_->projection() * camera_->view() * O * O_satellite * R_satellite * S_satellite;

    pyramid_->draw(PVM_satellite, u_pvm_buffer_);

    glBindVertexArray(vao_);
    glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_SHORT, reinterpret_cast<GLvoid *>(0));
    glBindVertexArray(0);
}

void SimpleShapeApplication::framebuffer_resize_callback(int w, int h) {
    Application::framebuffer_resize_callback(w, h);
    glViewport(0,0,w,h);
    camera_->perspective(glm::pi<float>()/4.0, (float)w/h, 0.1f, 100.0f);
}

void SimpleShapeApplication::mouse_button_callback(int button, int action, int mods) {
    Application::mouse_button_callback(button, action, mods);

    if (controler_) {
        double x, y;
        glfwGetCursorPos(window_, &x, &y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
            controler_->LMB_pressed(x, y);

        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
            controler_->LMB_released(x, y);
    }

}

void SimpleShapeApplication::cursor_position_callback(double x, double y) {
    Application::cursor_position_callback(x, y);
    if (controler_) {
        controler_->mouse_moved(x, y);
    }
}