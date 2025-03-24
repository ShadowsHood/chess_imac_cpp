#pragma once
#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

class App {
public:
  Board board;
  ImFont *main_font{};
  GLuint vao{};
  GLuint vbo{};
  GLFWwindow *window{};

  App() = default;
  void launch();

private:
  void init_font();
  void chess_2D();

  void init_3D();
  void terminate_3D();
  void chess_3D();
};