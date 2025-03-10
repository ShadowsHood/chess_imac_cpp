#include "./Board.hpp"
#include "./draw.hpp"
#include "./move.hpp"
#include "./pieces/Bishop.hpp"
#include "./pieces/King.hpp"
#include "./pieces/Knight.hpp"
#include "./pieces/Pawn.hpp"
#include "./pieces/Piece.hpp"
#include "./pieces/Queen.hpp"
#include "./pieces/Rook.hpp"
#include "./utils.hpp"
#include "quick_imgui/quick_imgui.hpp"
#include <array>
#include <imgui.h>
#include <iostream>
#include <optional>
#include <vector>

int main() {
  Board board;
  Color current_player = Color::White;
  std::vector<int> next_possible_moves{};
  std::optional<int> selected_piece_position{};
  bool moving = false;
  // bool this_tile_is_a_possible_move = false;

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

        ImGui::ShowDemoWindow(); // This opens a window with examples.

        if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
          deselect_piece(moving, selected_piece_position, next_possible_moves);
        
        ImGui::Begin("Chess Game");
        ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);
        set_background_color();

        // Draw the board
        draw_dead_pieces(board.dead_white_pieces, main_font);
        board.draw_board(next_possible_moves,moving, current_player,this_tile_is_a_possible_move, main_font);
        ImGui::Spacing();
        draw_dead_pieces(board.dead_black_pieces, main_font);

        ImGui::End();
      });
}