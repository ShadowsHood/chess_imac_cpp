#include "./App.hpp"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glad/glad.h>

void App::launch() {
  init_font();

  quick_imgui::loop(
      "Quick ImGui",
      {
          .init =
              [this]() {
                std::cout << "Init\n";
                // Get the window
                window = glfwGetCurrentContext();
                if (!window) {
                  std::cerr << "Error in getting the window" << '\n';
                }
                init_3D();
              },
          .loop =
              [this]() {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                  board.deselect_piece();
                chess_2D();
                chess_3D();
              },
          .key_callback =
              [](int key, int scancode, int action, int mods) {
                std::cout << "Key: " << key << " Scancode: " << scancode
                          << " Action: " << action << " Mods: " << mods << '\n';
              },
          .mouse_button_callback =
              [](int button, int action, int mods) {
                std::cout << "Button: " << button << " Action: " << action
                          << " Mods: " << mods << '\n';
              },
          .cursor_position_callback =
              [](double xpos, double ypos) {
                std::cout << "Position: " << xpos << ' ' << ypos << '\n';
              },
          .scroll_callback =
              [](double xoffset, double yoffset) {
                std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n';
              },
          .window_size_callback =
              [](int width, int height) {
                std::cout << "Resized: " << width << ' ' << height << '\n';
              },
      });
  terminate_3D();
}

void App::init_font() {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  main_font = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 60.0f);
  IM_ASSERT(main_font != nullptr);
}

void App::chess_2D() {
  ImGui::Begin("Chess Game");
  ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
  set_background_color();

  // Draw the board
  draw_dead_pieces(board, Color::White, main_font);
  draw_board(board, main_font);
  ImGui::Spacing();
  draw_dead_pieces(board, Color::Black, main_font);

  ImGui::End();
}

void App::chess_3D() {
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

void App::init_3D() {

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

void App::terminate_3D() {

  // Libérer la mémoire
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);

  //   glfwTerminate();
}