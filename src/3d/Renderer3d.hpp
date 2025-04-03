#pragma once

#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <glm/glm.hpp>
#include <imgui.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Renderer3d {
public:
  GLuint vao{};
  GLuint vbo{};
  glfeur::Shader shader;
  glfeur::Camera camera{true};
  int window_width = 1280;
  int window_height = 720;

  Model3D model;

  Renderer3d() = default;

  void init_3d();
  void terminate_3d();
  void chess_3d();
};