// #include "draw.hpp"
// #include "board.hpp"
// #include <string>

// void Board::draw_board(std::vector<int> &next_possible_moves, bool &moving,
//                        Color &current_player, bool &is_a_possible_move,
//                        ImFont *main_font) {
//   for (int i = 0; i < 64; i++) {
//     ImGui::PushID(i);
//     if (i % 8 != 0)
//       ImGui::SameLine();

//     // Set color of the tile (black or white)
//     ImVec4 tileColor = get_tile_color(i);
//     ImGui::PushStyleColor(ImGuiCol_Button, tileColor);

//     Piece *piece = this->get_piece(i);
//     // Set the name of the piece
//     std::string name =
//         (piece != nullptr) ? std::string(1, piece->get_char()) : "";
//     // std::string buttonLabel = name + "##" + std::to_string(i);

//     if (piece != nullptr) push_font(piece, main_font);
//     is_a_possible_move = is_possible_move(next_possible_moves, i);
//     // Possible moves highlight
//     if (is_a_possible_move) push_possible_move_color();

//     // Draw tiles
//     if (ImGui::Button(name.c_str(), ImVec2{100.f, 100.f}) &&
//         !this->is_empty(i)) {

//       // Current player
//       if (this->get_piece(i)->get_color() == current_player) {
//         std::cout << "Clicked button : " << i << " ==> (" << get_pos_2D(i).first
//                   << "," << get_pos_2D(i).second << ") \n";
//         moving = true;
//         next_possible_moves = this->get_piece(i)->get_possible_moves(*this, i);

//       } else {
//         std::cout << "Not your turn\n";
//       }
//     }

//     if (piece != nullptr) pop_font();
//     // Pop possible moves highlight
//     if (is_a_possible_move) pop_possible_move_color();
//     // Pop tile color (black or white)
//     ImGui::PopStyleColor();
//     ImGui::PopID();
//   }
// }

// ImVec4 get_tile_color(int i) {
//   int x = i % 8;
//   int y = i / 8;
//   return (x + y) % 2 == 0 ? ImVec4{0.8f, 0.8f, 0.8f, 1.f}
//                           : ImVec4{0.4f, 0.2f, 0.8f, 1.f};
//   //   return (x + y) % 2 == 0 ? ImVec4{0.8f, 0.8f, 0.8f, 1.f}
//   //                           : ImVec4{0.2f, 0.2f, 0.2f, 1.f};
// }

// bool is_possible_move(std::vector<int> &next_possible_moves, int i) {
//   return std::find(next_possible_moves.begin(), next_possible_moves.end(), i) !=
//          next_possible_moves.end();
// }

// // Font
// void push_font(Piece *piece, ImFont *&main_font) {
//   ImGui::PushFont(main_font);
//   ImGui::PushStyleColor(ImGuiCol_Text, (piece->get_color() == Color::Black)
//                                            ? IM_COL32(25, 25, 25, 255)
//                                            : IM_COL32(250, 250, 250, 255));
// }
// void pop_font() {
//   ImGui::PopFont();
//   ImGui::PopStyleColor();
// }

// // Possible move highlight
// void push_possible_move_color() {
//   ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize,
//                       5.0f); // Set border size
//   ImGui::PushStyleColor(ImGuiCol_Border,
//                         IM_COL32(0, 255, 0, 255)); // Set border color to green
//   ImGui::PushStyleColor(
//       ImGuiCol_Button,
//       ImVec4{0.6f, 0.8f, 0.6f, 1.f}); // Set border color to green
// }
// void pop_possible_move_color() {
//     ImGui::PopStyleColor();
//       ImGui::PopStyleColor();
//       ImGui::PopStyleVar();
// }

// // Colors
// void push_colors(ImFont *&main_font) {}
// void pop_colors(ImFont *&main_font) {}