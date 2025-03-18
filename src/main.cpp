#include "./draw.hpp"
#include "./elements/Board.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <imgui.h>
#include <iostream>

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
        draw_dead_pieces(board, Color::White, main_font);
        draw_board(board, main_font);
        ImGui::Spacing();
        draw_dead_pieces(board, Color::Black, main_font);

        if (board.get_is_popup_open()) {
          ImGui::OpenPopup("Promotion of your pawn"); // On ouvre la popup UNE SEULE FOIS
          // board.set_is_popup_open(false); // On désactive immédiatement le flag
        }   

        ImGui::End();
      });
}