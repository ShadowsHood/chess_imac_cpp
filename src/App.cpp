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
                // std::cout << "Init\n";
                renderer3d.init_3d();
              },
          .loop =
              [this]() {
                if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
                  board.deselect_piece();
                chess_2d();
                renderer3d.chess_3d();
              },
          // .key_callback =
          //     [](int key, int scancode, int action, int mods) {
          //       std::cout << "Key: " << key << " Scancode: " << scancode
          //                 << " Action: " << action << " Mods: " << mods << '\n';
          //     },
          // .mouse_button_callback =
          //     [](int button, int action, int mods) {
          //       std::cout << "Button: " << button << " Action: " << action
          //                 << " Mods: " << mods << '\n';
          //     },
          // .cursor_position_callback =
          //     [](double xpos, double ypos) {
          //       std::cout << "Position: " << xpos << ' ' << ypos << '\n';
          //     },
          // .scroll_callback =
          //     [](double xoffset, double yoffset) {
          //       std::cout << "Scroll: " << xoffset << ' ' << yoffset << '\n';
          //     },
          // .window_size_callback =
          //     [](int width, int height) {
          //       std::cout << "Resized: " << width << ' ' << height << '\n';
          //     },
      });
  renderer3d.terminate_3d();
}

void App::init_font() {
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  main_font = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 60.0f);
  IM_ASSERT(main_font != nullptr);
}

void App::chess_2d() {
  ImGui::Begin("Chess Game");
  ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
  set_background_color();

  // Draw the board
  draw_dead_pieces(board, Color::White, main_font);
  draw_board(board, main_font);
  ImGui::Spacing();
  draw_dead_pieces(board, Color::Black, main_font);

  // Handle the popup of pawns promotion
  if (board.is_promotion_activated()) {
    board.handle_promotion(main_font);
  }

  ImGui::End();
}