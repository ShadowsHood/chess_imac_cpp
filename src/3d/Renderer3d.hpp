#pragma once

#include "../elements/Board.hpp"
#include "../elements/Type.hpp"
#include "Camera.hpp"
#include "Model3D.hpp"
#include "Shader.hpp"
#include <glm/glm.hpp>
#include <imgui.h>
#include <map>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>
// #include <thread>

class Renderer3d {
public:
  GLuint vao{};
  GLuint vbo{};
  glfeur::Shader shader;
  glfeur::Camera camera{true};
  int window_width = 1920;
  int window_height = 1080;

  std::map<Type, Model3D> models;
  bool models_ready = false;
  Model3D cube_model;

  Model3D skybox_model;
  GLuint skybox_texture;
  glfeur::Shader skybox_shader;

  Renderer3d() = default;

  void init_3d();
  void load_models_async();
  void terminate_3d();
  void chess_3d(Board const &board);
  void render_tile(int index, float tile_size, float tile_spacing,
                   std::array<float, 32> const &tiles_color_offsets);
  void render_base(float tile_size, float tile_spacing);
  void render_piece(Type type, Color color, int index, float tile_size,
                    float tile_spacing);

  void load_skybox(std::vector<std::string> faces);
  GLuint load_cubemap(std::vector<std::string> faces);
};