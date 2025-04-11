#include "./Renderer3d.hpp"
#include "../utils.hpp"
#include "glm/ext/matrix_clip_space.hpp"
#include "glm/fwd.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

void Renderer3d ::chess_3d(Board const &board) {
  glClearColor(0.5f, 0.1f, 0.2f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);

  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          static_cast<float>(window_width) /
                                              static_cast<float>(window_height),
                                          0.1f, 100.0f);

  shader.use();

  // MVP
  shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
  shader.set_uniform_matrix_4fv("projection", projection);

  // LIGHT SETTINGS
  if (board.get_current_player() == Color::White) {
    shader.set_uniform_3fv("lightPos", glm::vec3(0.0f, 5.0f, 2.0f));
    shader.set_uniform_3fv("lightColor", glm::vec3(0.85f, 0.9f, 0.7f));
  } else {
    shader.set_uniform_3fv("lightPos", glm::vec3(0.0f, 5.0f, -2.0f));
    shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 0.7f, 0.5f));
  }

  // LIGHT SETTINGS (2nd)
  float time = glfwGetTime();
  float radius = 5.0f; // Rayon de la rotation
  float lightX = radius * std::cos(time);
  float lightZ = radius * std::sin(time);
  shader.set_uniform_3fv("lightPos2", glm::vec3(lightX, 4.0f, lightZ));
  shader.set_uniform_3fv("lightColor2", glm::vec3(0.4f, 0.1f, 1.0f));

  // CAMERA SETTINGS
  shader.set_uniform_3fv("viewPos", camera.get_position());
  shader.set_uniform_3fv("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));

  // Board render
  float tile_size = 0.7f;
  float tile_spacing = 0.2f;
  render_base(tile_size, tile_spacing);
  for (int i = 0; i < 64; ++i) {
    render_tile(i, tile_size, tile_spacing, board.get_tiles_color_offsets());
    if (!models_ready) {
      std::cout << "Chargement des modeles...\n";
    } else {
      if (!board.is_empty(i)) {
        Type type = board[i]->get_type();
        Color color = board[i]->get_color();
        render_piece(type, color, i, tile_size, tile_spacing);
      }
    }
  }

  // SKYBOX
  glDepthFunc(GL_LEQUAL); // Change depth function so depth test passes when
                          // values are equal to depth buffer's content
  skybox_shader.use();
  glm::mat4 view = glm::mat4(glm::mat3(
      camera.get_view_matrix())); // remove translation part of view matrix
  skybox_shader.set_uniform_matrix_4fv("view", view);
  skybox_shader.set_uniform_matrix_4fv("projection", projection);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_CUBE_MAP, skybox_texture);
  skybox_model.render(skybox_shader);
  glDepthFunc(GL_LESS); // set depth function back to default
}

void Renderer3d ::render_piece(Type type, Color color, int index,
                               float tile_size, float tile_spacing) {
  glm::mat4 model_matrix = glm::mat4(1.0f);
  glm::vec3 position = get_pos_3D(index, tile_size, tile_spacing);

  model_matrix = glm::translate(
      model_matrix, glm::vec3(-(tile_size * 8), 0.3f, -(tile_size * 8)));
  model_matrix = glm::translate(model_matrix, position);
  if (color == Color::White)
    model_matrix =
        glm::rotate(model_matrix, glm::radians(180.0f), glm::vec3(0, 1, 0));

  shader.set_uniform_matrix_4fv("model", model_matrix);
  shader.set_uniform_3fv("objectColor", color == Color::Black
                                            ? glm::vec3(0.35f, 0.20f, 0.f)
                                            : glm::vec3(0.85f, 0.85f, 0.8f));

  models[type].render(shader);
}

void Renderer3d ::render_tile(
    int index, float tile_size, float tile_spacing,
    std::array<float, 32> const &tiles_color_offsets) {
  glm::mat4 tileMatrix = glm::mat4(1.0f);
  glm::vec3 position = get_pos_3D(index, tile_size, tile_spacing);

  tileMatrix = glm::translate(
      tileMatrix, glm::vec3(-(tile_size * 8), 0.0f, -(tile_size * 8)));
  tileMatrix = glm::translate(tileMatrix, position);
  tileMatrix = glm::scale(tileMatrix, glm::vec3(tile_size, 0.1, tile_size));
  int rotation = index * index % 3;
  tileMatrix = glm::rotate(tileMatrix,
                           glm::radians(90.0f * static_cast<float>(rotation)),
                           glm::vec3(0, 1, 0));

  shader.set_uniform_matrix_4fv("model", tileMatrix);
  shader.set_uniform_3fv("objectColor",
                         get_tile_color_vec3(index, tiles_color_offsets));

  cube_model.render(shader);
}

void Renderer3d ::render_base(float tile_size, float tile_spacing) {
  glm::mat4 tileMatrix = glm::mat4(1.0f);
  glm::vec3 position{0.0f, -0.1, 0.0f};

  float base_size = (tile_size * 8) + (tile_spacing * 6);
  tileMatrix = glm::translate(tileMatrix, position);
  tileMatrix = glm::scale(tileMatrix, glm::vec3(base_size, 0.04, base_size));

  shader.set_uniform_matrix_4fv("model", tileMatrix);
  shader.set_uniform_3fv("objectColor", glm::vec3(0.25f, 0.25f, 0.25f));

  cube_model.render(shader);
}

void Renderer3d ::init_3d() {
  shader.load_shader("model.vs.glsl", "model.fs.glsl");
  models.clear();
  cube_model.load_mesh("tile/tile_3.obj", "tile");
  cube_model.setup_buffers();
  models_ready = false;
  load_models_async();

  skybox_shader.load_shader("skybox.vs.glsl", "skybox.fs.glsl");
  load_skybox({"skybox/right.jpg", "skybox/left.jpg", "skybox/top.jpg",
               "skybox/bottom.jpg", "skybox/front.jpg", "skybox/back.jpg"});
}

void Renderer3d::load_models_async() {
  // loader_thread = std::thread([this]() {
  std::vector<std::pair<Type, std::string>> model_data = {
      {Type::Pawn, "pawn/pawn.obj"},
      {Type::Well, "well/well.obj"},
      {Type::Queen, "queen/queen.obj"},
      {Type::King, "king/king.obj"},
      {Type::Racist, "racist/racist.obj"},
      {Type::Kamikaze, "kamikaze/kamikaze.obj"},
      {Type::Fool, "fool/fool.obj"},
      {Type::Rook, "rook/rook.obj"},
      {Type::Knight, "knight/knight.obj"},
      {Type::Bishop, "bishop/bishop.obj"}};

  for (const auto &data : model_data) {
    Model3D model;
    model.load_mesh(data.second, type_string(data.first));
    models.insert({data.first, std::move(model)});
  }

  for (auto &[type, model] : models) {
    model.setup_buffers();
  }

  std::cout << "Chargement termine\n";
  models_ready = true;
}

void Renderer3d ::terminate_3d() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

//
//
//
// SKYBOX
//
//
//
void Renderer3d::load_skybox(std::vector<std::string> faces) {
  skybox_model.load_mesh("skybox/skybox.obj",
                         "skybox"); // Charge un cube simple
  skybox_model.setup_buffers();

  skybox_texture = load_cubemap(faces); // Fonction pour charger les textures
}

GLuint Renderer3d::load_cubemap(std::vector<std::string> faces) {
  GLuint textureID;
  glGenTextures(1, &textureID);
  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

  int width, height, nrChannels;
  unsigned char *data;
  for (unsigned int i = 0; i < faces.size(); i++) {
    std::string path = "assets/img/" + faces[i];
    data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
    if (data) {
      glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                   0, GL_RGB, GL_UNSIGNED_BYTE, data);
      stbi_image_free(data);
    } else {
      std::cerr << "Cubemap texture failed to load at path: " << faces[i]
                << std::endl;
      stbi_image_free(data);
    }
  }
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

  return textureID;
}