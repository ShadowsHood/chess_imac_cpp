#pragma once

#include "../elements/Board.hpp"
#include "../elements/Type.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <glm/glm.hpp>
#include <imgui.h>
#include <iostream>
#include <map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <thread>

class Renderer3d {
public:
  GLuint vao{};
  GLuint vbo{};
  glfeur::Shader shader;
  glfeur::Camera camera{true};
  int window_width = 1920;
  int window_height = 1080;

  std::map<Type, Model3D> models;
  // std::thread loader_thread;
  bool models_ready = false;
  Model3D cube_model;

  Renderer3d() = default;

  void init_3d();
  void load_models_async();
  void terminate_3d();
  void chess_3d(Board const &board);
  void render_tile(int index, float tileSize, float tileSpacing);
  void render_base(float tileSize, float tileSpacing);
  void render_piece(Type type, Color color, int index, float tileSize,
                    float tileSpacing);
};