#include "./Board.hpp"
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
#include <vector>

int main() {
  std::vector<int> next_possible_moves{};
  bool moving = false;
  Color current_player = Color::White;
  Board board;
  bool this_tile_is_a_possible_move = false;

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
        ImGui::ShowDemoWindow(); // This opens a window which shows tons of
                                 // examples of what you can do with ImGui. You
                                 // should check it out! Also, you can use the
                                 // "Item Picker" in the top menu of that demo
                                 // window: then click on any widget and it will
                                 // show you the corresponding code directly in
                                 // your IDE!

        ImGui::Begin("Chess Game");
        ImGui::GetStyle().ItemSpacing = ImVec2(0.0f, 0.0f);

        for (int i = 0; i < 64; i++) {
          ImGui::PushID(i);
          if (i % 8 != 0)
            ImGui::SameLine();

          ImVec4 buttonColor = (((i / 8) % 2 == 0) ^ (i % 2 == 0))
                                   ? ImVec4{0.4f, 0.2f, 0.2f, 1.f}
                                   : ImVec4{0.8f, 0.8f, 0.8f, 1.f};
          ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);

          Piece *piece = board.get_piece(i);
          // std::string name = (piece != nullptr)
          //                        ? std::string(1, piece->get_char())
          //                        : std::to_string(i);
          std::string name =
              (piece != nullptr) ? std::string(1, piece->get_char()) : "";
          std::string buttonLabel = name + "##" + std::to_string(i);

          if (piece != nullptr) {
            ImGui::PushFont(main_font);
            ImGui::PushStyleColor(ImGuiCol_Text,
                                  (piece->get_color() == Color::Black)
                                      ? IM_COL32(25, 25, 25, 255)
                                      : IM_COL32(250, 250, 250, 255));
          }

          // // Push style for border
          // ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize,
          //                     2.0f); // Set border size
          // ImGui::PushStyleColor(
          //     ImGuiCol_Border,
          //     IM_COL32(0, 255, 0, 255)); // Set border color to green

          this_tile_is_a_possible_move =
              std::find(next_possible_moves.begin(), next_possible_moves.end(),
                        i) != next_possible_moves.end()
                  ? true
                  : false;

          // Border selected
          if (this_tile_is_a_possible_move) {
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize,
                                2.0f); // Set border size
            ImGui::PushStyleColor(
                ImGuiCol_Button,
                ImVec4{0.2f, 0.4f, 0.2f, 1.f}); // Set border color to green
          }
          // Draw tiles
          if (ImGui::Button(name.c_str(), ImVec2{100.f, 100.f}) &&
              !board.is_empty(i)) {

            // Current player
            if (board.get_piece(i)->get_color() == current_player) {
              std::cout << "Clicked button : " << i << " ==> ("
                        << get_pos_2D(i).first << "," << get_pos_2D(i).second
                        << ") \n";
              moving = true;
              next_possible_moves =
                  board.get_piece(i)->get_possible_moves(board, i);

            } else {
              std::cout << "Not your turn\n";
            }
          }

          // Border selected
          if (this_tile_is_a_possible_move) {
            ImGui::PopStyleColor();
            ImGui::PopStyleVar();
          }

          if (piece != nullptr) {
            ImGui::PopFont();
            ImGui::PopStyleColor();
          }

          ImGui::PopStyleColor();
          ImGui::PopID();
        }

        ImGui::End();
      });
}