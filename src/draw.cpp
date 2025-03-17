#include "draw.hpp"
#include <string>
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
  // Set color of the tile (black or white)
  ImVec4 tileColor = get_tile_color(index);
  ImGui::PushStyleColor(ImGuiCol_Button, tileColor);

  // Set the name of the piece
  std::string name =
      (piece != nullptr) ? std::string(1, piece->get_char()) : "";
  // std::string buttonLabel = name + "##" + std::to_string(index);

  if (piece != nullptr)
    push_font(piece->get_color(), main_font);

  // Possible moves highlight
  if (is_a_possible_move)
    push_possible_move_color();

  // Draw tile
  if (ImGui::Button(name.c_str(), ImVec2{100.f, 100.f})) {
    if (board.get_in_game())
      board.handle_tile_click(index, piece,
                              is_a_possible_move); // std optional color ?
  }

  if (piece != nullptr)
    pop_font();
  // Pop possible moves highlight
  if (is_a_possible_move)
    pop_possible_move_color();
  // Pop tile color (black or white)
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

ImVec4 get_tile_color(int i) {
  int x = i % 8;
  int y = i / 8;
  return (x + y) % 2 == 0 ? ImVec4{0.8f, 0.8f, 0.8f, 1.f}
                          : ImVec4{0.4f, 0.2f, 0.8f, 1.f};
  //   return (x + y) % 2 == 0 ? ImVec4{0.8f, 0.8f, 0.8f, 1.f}
  //                           : ImVec4{0.2f, 0.2f, 0.2f, 1.f};
}

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
