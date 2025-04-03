#include "./Renderer3d.hpp"

void Renderer3d ::chess_3d() {
  // glClearColor(1.f, 0.5f, 0.5f, 1.f);
  // glClear(GL_COLOR_BUFFER_BIT);

  // // Nettoyer l'écran
  // glClear(GL_COLOR_BUFFER_BIT);

  // glBindVertexArray(vao);
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  // glBindVertexArray(0);

  glClearColor(0.847f, 0.82f, 0.929f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  //
  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          static_cast<float>(window_width) /
                                              static_cast<float>(window_height),
                                          0.1f, 100.0f);

  shader.use();

  // MVP
  shader.set_uniform_matrix_4fv("model", glm::mat4(1.0f));
  shader.set_uniform_matrix_4fv("view", camera.get_view_matrix());
  shader.set_uniform_matrix_4fv("projection", projection);

  // LIGHT SETTINGS
  shader.set_uniform_3fv("lightPos", glm::vec3(5.0f, 5.0f, 5.0f));
  shader.set_uniform_3fv("lightColor", glm::vec3(1.0f, 1.0f, 1.0f));

  // CAMERA SETTINGS
  shader.set_uniform_3fv("viewPos", camera.get_position());

  // MODEL RENDER
  model.render(shader);
}

void Renderer3d ::init_3d() {

  // // Le VBO contient les données
  // glGenBuffers(1, &vbo);
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
  // glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices,
  // GL_STATIC_DRAW); glBindBuffer(GL_ARRAY_BUFFER, 0);

  // // Le VAO décrit les données
  // glGenVertexArrays(1, &vao);
  // glBindVertexArray(vao);
  // const GLuint VERTEX_ATTR_POSITION = 0;
  // glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE,
  //                       2 * sizeof(GLfloat), nullptr);
  // glBindBuffer(GL_ARRAY_BUFFER, 0);
  // glBindVertexArray(0);

  shader.load_shader("model.vs.glsl", "model.fs.glsl");
  model.load_mesh("creeper/creeper.obj", "creeper");
  model.setup_buffers();
}

void Renderer3d ::terminate_3d() {

  // Libérer la mémoire
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  //   glfwTerminate();
}