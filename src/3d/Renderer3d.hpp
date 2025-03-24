#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class Renderer3d {
public:
  GLuint vao{};
  GLuint vbo{};

  Renderer3d() = default;

  void init_3d();
  void terminate_3d();
  void chess_3d();
};