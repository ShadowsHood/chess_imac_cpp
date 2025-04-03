#include "./Renderer3d.hpp"

void Renderer3d ::chess_3d() {
  glClearColor(1.f, 0.5f, 0.5f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Nettoyer l'écran
  glClear(GL_COLOR_BUFFER_BIT);

  glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
  glBindVertexArray(0);

  //   glfwSwapBuffers(window);
  //   glfwPollEvents();
}

void Renderer3d ::init_3d() {

  // Le VBO contient les données
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GLfloat vertices[] = {-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.5f};
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(GLfloat), vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Le VAO décrit les données
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  const GLuint VERTEX_ATTR_POSITION = 0;
  glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glVertexAttribPointer(VERTEX_ATTR_POSITION, 2, GL_FLOAT, GL_FALSE,
                        2 * sizeof(GLfloat), nullptr);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Renderer3d ::terminate_3d() {

  // Libérer la mémoire
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  //   glfwTerminate();
}