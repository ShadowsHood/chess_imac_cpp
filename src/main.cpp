#include "./Board.hpp"
#include "./draw.hpp"
#include "./pieces/Piece.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>

int main() {
  Board board;

  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();
  io.Fonts->AddFontDefault();
  ImFont *main_font = io.Fonts->AddFontFromFileTTF("fonts/CHEQ_TT.TTF", 60.0f);
  IM_ASSERT(main_font != nullptr);

  quick_imgui::loop(
      "Chess",
      /* init: */ [&]() {},
      /* loop: */
      [&]() {
        // ImGui::ShowDemoWindow(); // This opens a window with examples.

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
          board.deselect_piece();

        ImGui::Begin("Chess Game");
        ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
        set_background_color();

        // Draw the board
        board.draw_dead_pieces(Color::White, main_font);
        board.draw_board(main_font);
        ImGui::Spacing();
        board.draw_dead_pieces(Color::Black, main_font);

        ImGui::End();
      });
}