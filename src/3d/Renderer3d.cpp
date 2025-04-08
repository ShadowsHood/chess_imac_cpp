#include "./Renderer3d.hpp"
#include <glm/gtc/matrix_transform.hpp>

void Renderer3d ::chess_3d() {
  glClearColor(0.5f, 0.1f, 0.2f, 1.f);
  // glClearColor(0.847f, 0.82f, 0.929f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  //
  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          static_cast<float>(window_width) /
                                              static_cast<float>(window_height),
                                          0.1f, 100.0f);

  shader.use();

  // MVP
  shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
  shader.set_uniform_matrix_4fv("projection", projection);

  // LIGHT SETTINGS
  shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
  shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

  // CAMERA SETTINGS
  shader.set_uniform_3fv("viewPos", camera.get_position());

  // MODEL RENDER
  // for (const auto &model : models) {
  //   glm::mat4 modelMatrix = model.get_model_matrix(); // Each model has its
  //   own transformation shader.set_uniform_matrix_4fv("model", modelMatrix);
  //   model.render(shader); // Render the model
  // }
  for (size_t i = 0; i < models.size(); ++i) {

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.2f));
    modelMatrix = glm::translate(modelMatrix, glm::vec3(i * 2.0f, 0.0f, 0.0f));

    shader.set_uniform_matrix_4fv("model", modelMatrix);
    models[i].render(shader);
  }
}

void Renderer3d ::init_3d() {
  shader.load_shader("model.vs.glsl", "model.fs.glsl");

  models.clear();

  Model3D model1;
  Model3D model2;
  model1.load_mesh("creeper/creeper.obj", "creeper");
  model2.load_mesh("pawn/pawn.obj", "pawn");

  models.push_back(std::move(model1));
  models.push_back(std::move(model2));

  for (auto &model : models) {
    model.setup_buffers();
  }
}

void Renderer3d ::terminate_3d() {
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}