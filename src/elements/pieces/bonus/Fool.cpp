#include "./Fool.hpp"
#include "../../Board.hpp" // Include the full definition of Board
#include "utils.hpp"

std::vector<int> Fool::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  bool empty{};
  bool color{};
  for (int i = 0; i < 64; i++) {
    if (board.is_empty(i) || board.is_other_color(i, this->get_color())) {
      possible_moves.push_back(i);
    }
  }
  display_vector_pos(possible_moves);
  return possible_moves;
}