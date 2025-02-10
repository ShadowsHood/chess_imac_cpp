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
  std::vector<int> next_possible_moves;
  bool moving = false;
  Color current_player = Color::White;
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
        ImGui::ShowDemoWindow(); // This opens a window which shows tons of
                                 // examples of what you can do with ImGui. You
                                 // should check it out! Also, you can use the
                                 // "Item Picker" in the top menu of that demo
                                 // window: then click on any widget and it will
                                 // show you the corresponding code directly in
                                 // your IDE!

        ImGui::Begin("Example");

        for (int i = 0; i < 64; i++) {
          ImGui::PushID(i);
          if (i % 8 != 0)
            ImGui::SameLine();

          ImVec4 buttonColor = (((i / 8) % 2 == 0) ^ (i % 2 == 0))
                                   ? ImVec4{0.4f, 0.2f, 0.2f, 1.f}
                                   : ImVec4{0.8f, 0.8f, 0.8f, 1.f};
          ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);

          Piece *piece = board.get_piece(get_pos_2D(i));
          std::string name = (piece != nullptr)
                                 ? std::string(1, piece->get_char())
                                 : std::to_string(i);
          std::string buttonLabel = name + "##" + std::to_string(i);

          if (piece != nullptr) {
            ImGui::PushFont(main_font);
            ImGui::PushStyleColor(ImGuiCol_Text,
                                  (piece->get_color() == Color::Black)
                                      ? IM_COL32(25, 25, 25, 255)
                                      : IM_COL32(250, 250, 250, 255));
          }
          if (ImGui::Button(buttonLabel.c_str(), ImVec2{100.f, 100.f}))
            std::cout << "Clicked button " << i << "\n";
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