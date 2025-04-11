#include "draw.hpp"
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

void set_background_color() {
  ImGui::StyleColorsDark();
  ImVec4 *colors = ImGui::GetStyle().Colors;
  ImGui::GetStyle().Colors[ImGuiCol_WindowBg] = ImVec4(0.4f, 0.4f, 0.4f, 1.0f);
}

void draw_board(Board &board, ImFont *main_font) {

  for (int i = 0; i < 64; i++) {
    ImGui::PushID(i);
    if (i % 8 != 0)
      ImGui::SameLine();

    Piece const *piece = board[i];
    bool is_a_possible_move =
        is_possible_move(board.get_next_possible_moves(), i);

    draw_tile(board, i, piece, main_font, is_a_possible_move);

    ImGui::PopID();
  }
}

void draw_tile(Board &board, int index, Piece const *piece, ImFont *main_font,
               bool &is_a_possible_move) {
  // Set color of the tile
  ImVec4 tileColor = get_tile_color(index, board.get_tiles_color_offsets());
  ImGui::PushStyleColor(ImGuiCol_Button, tileColor);

  // Set the name of the piece
  std::string name =
      (piece != nullptr) ? std::string(1, piece->get_char()) : "";

  if (piece != nullptr)
    push_font(piece->get_color(), main_font);

  // Possible moves highlight
  if (is_a_possible_move)
    push_possible_move_color();

  // Draw tile
  if (ImGui::Button(name.c_str(), ImVec2{60.f, 60.f})) {
    if (board.get_in_game())
      board.handle_tile_click(index, piece, is_a_possible_move);
  }

  if (piece != nullptr)
    pop_font();
  if (is_a_possible_move)
    pop_possible_move_color();
  ImGui::PopStyleColor();
}

void draw_dead_pieces(const Board &board, Color color, ImFont *main_font) {
  std::vector<Piece const *> dead_pieces = board.get_dead_pieces(color);

  for (Piece const *piece : dead_pieces) {
    push_font(piece->get_color(), main_font);
    ImGui::SameLine();
    std::string name = std::string(1, piece->get_char());
    ImGui::Text("%s", name.c_str());
    pop_font();
  }
}

char draw_promotion_popup(ImFont *main_font, Color color) {
  char new_type{};
  ImVec2 center = ImGui::GetMainViewport()->GetCenter();
  ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

  if (ImGui::BeginPopupModal("Promotion of your pawn", nullptr,
                             ImGuiWindowFlags_AlwaysAutoResize)) {
    ImGui::Text("Choose a piece for promotion:");
    ImGui::Dummy(ImVec2(0.0f, 20.0f));
    ImGui::PushFont(main_font);

    // Font color & buttons color
    ImVec4 textColor = (color == Color::Black) ? ImVec4(1.0f, 1.0f, 1.0f, 1.0f)
                                               : ImVec4(0.0f, 0.0f, 0.0f, 1.0f);
    ImVec4 buttonColor = ImVec4(0.5f, 0.5f, 0.5f, 1.0f);
    ImGui::PushStyleColor(ImGuiCol_Text, textColor);
    ImGui::PushStyleColor(ImGuiCol_Button, buttonColor);

    // Buttons to choose the new piece
    std::unordered_map<char, Type> types = {
        {'q', Type::Queen},  {'r', Type::Rook},   {'k', Type::Knight},
        {'b', Type::Bishop}, {'n', Type::Racist}, {'f', Type::Fool},
        {'w', Type::Well}};

    for (auto &[key, type] : types) {
      std::string spriteChar(1, get_sprite_char(color, type));
      if (ImGui::Button((spriteChar + "##" + key).c_str(),
                        ImVec2{100.f, 100.f})) {
        std::cout << "New type: " << key << '\n';
        new_type = key;
        ImGui::CloseCurrentPopup();
      }
      ImGui::SameLine(0, 10);
    }

    ImGui::PopStyleColor(2);
    ImGui::PopFont();
    ImGui::EndPopup();
  }
  return new_type;
}

// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -
// -

bool is_possible_move(const std::vector<int> &next_possible_moves, int i) {
  return std::find(next_possible_moves.begin(), next_possible_moves.end(), i) !=
         next_possible_moves.end();
}

// Font
void push_font(Color color, ImFont *&main_font) {
  ImGui::PushFont(main_font);
  ImGui::PushStyleColor(ImGuiCol_Text, (color == Color::Black)
                                           ? IM_COL32(25, 25, 25, 255)
                                           : IM_COL32(250, 250, 250, 255));
}
void pop_font() {
  ImGui::PopFont();
  ImGui::PopStyleColor();
}

// Possible move highlight
void push_possible_move_color() {
  ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize,
                      5.0f); // Set border size
  ImGui::PushStyleColor(ImGuiCol_Border,
                        IM_COL32(0, 255, 0, 255)); // Set border color to green
  ImGui::PushStyleColor(
      ImGuiCol_Button,
      ImVec4{0.6f, 0.8f, 0.6f, 1.f}); // Set border color to green
}
void pop_possible_move_color() {
  ImGui::PopStyleColor();
  ImGui::PopStyleColor();
  ImGui::PopStyleVar();
}
