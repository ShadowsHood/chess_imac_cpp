#include "./Renderer3d.hpp"
#include "../utils.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Renderer3d ::chess_3d(Board const &board) {
  glClearColor(0.5f, 0.1f, 0.2f, 1.f);
  // glClearColor(0.847f, 0.82f, 0.929f, 1.f);
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
  shader.set_uniform_3fv("lightPos", glm::vec3(2.0f, 5.0f, 2.0f));
  shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 0.9f));

  // CAMERA SETTINGS
  shader.set_uniform_3fv("viewPos", camera.get_position());
  shader.set_uniform_3fv("objectColor", glm::vec3(1.0f, 0.0f, 0.0f));

  // Board render
  float tileSize = 0.7f;
  float tileSpacing = 0.2f;
  render_base(tileSize, tileSpacing);
  for (int i = 0; i < 64; ++i) {
    render_tile(i, tileSize, tileSpacing, board.get_tiles_color_offsets());
    if (!models_ready) {
      std::cout << "Chargement des modèles...\n";
    } else {
      if (!board.is_empty(i)) {
        Type type = board[i]->get_type();
        Color color = board[i]->get_color();
        render_piece(type, color, i, tileSize, tileSpacing);
      }
    }
  }

  // int index{0};
  // for (auto &[type, model] : models) {
  //   glm::mat4 modelMatrix = glm::mat4(1.0f);
  //   // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
  //   modelMatrix =
  //       glm::translate(modelMatrix, glm::vec3(index * 2.0f, 0.0f, 0.0f));

  //   shader.set_uniform_matrix_4fv("model", modelMatrix);
  //   model.render(shader);
  //   index++;
  // }
}

void Renderer3d ::render_piece(Type type, Color color, int index,
                               float tileSize, float tileSpacing) {
  glm::mat4 modelMatrix = glm::mat4(1.0f);
  glm::vec3 position = get_pos_3D(index, tileSize, tileSpacing);

  modelMatrix = glm::translate(
      modelMatrix, glm::vec3(-(tileSize * 8), 0.3f, -(tileSize * 8)));
  modelMatrix = glm::translate(modelMatrix, position);
  if (color == Color::White)
    modelMatrix =
        glm::rotate(modelMatrix, glm::radians(180.0f), glm::vec3(0, 1, 0));

  shader.set_uniform_matrix_4fv("model", modelMatrix);
  shader.set_uniform_3fv("objectColor", color == Color::Black
                                            ? glm::vec3(0.35f, 0.15f, 0.0f)
                                            : glm::vec3(0.8f, 0.8f, 0.8f));

  models[type].render(shader);
}

void Renderer3d ::render_tile(
    int index, float tileSize, float tileSpacing,
    std::array<float, 32> const &tiles_color_offsets) {
  glm::mat4 tileMatrix = glm::mat4(1.0f);
  glm::vec3 position = get_pos_3D(index, tileSize, tileSpacing);

  tileMatrix = glm::translate(
      tileMatrix, glm::vec3(-(tileSize * 8), 0.0f, -(tileSize * 8)));
  tileMatrix = glm::translate(tileMatrix, position);
  tileMatrix = glm::scale(tileMatrix, glm::vec3(tileSize, 0.1, tileSize));
  int rotation = index * index % 3;
  tileMatrix = glm::rotate(tileMatrix, glm::radians(90.0f * rotation),
                           glm::vec3(0, 1, 0));

  shader.set_uniform_matrix_4fv("model", tileMatrix);
  shader.set_uniform_3fv("objectColor",
                         get_tile_color_vec3(index, tiles_color_offsets));

  cube_model.render(shader);
}

void Renderer3d ::render_base(float tileSize, float tileSpacing) {
  glm::mat4 tileMatrix = glm::mat4(1.0f);
  glm::vec3 position{0.0f, -0.1, 0.0f};

  float base_size = (tileSize * 8) + (tileSpacing * 6);
  tileMatrix = glm::translate(tileMatrix, position);
  tileMatrix = glm::scale(tileMatrix, glm::vec3(base_size, 0.04, base_size));

  shader.set_uniform_matrix_4fv("model", tileMatrix);
  shader.set_uniform_3fv("objectColor", glm::vec3(0.25f, 0.25f, 0.25f));

  cube_model.render(shader);
}

void Renderer3d ::init_3d() {
  shader.load_shader("model.vs.glsl", "model.fs.glsl");
  models.clear();
  cube_model.load_mesh("tile/tile_2.obj", "tile");
  cube_model.setup_buffers();
  models_ready = false;
  load_models_async();
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

  std::cout << "Chargement terminé\n";
  models_ready = true;
  // });
  // loader_thread.join();
}

void Renderer3d ::terminate_3d() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}