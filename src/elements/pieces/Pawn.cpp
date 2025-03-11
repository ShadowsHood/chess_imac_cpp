#include "./Pawn.hpp"
#include "../move.hpp"
#include "utils.hpp"

std::vector<int> Pawn::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_pawn_moves(possible_moves, board, get_pos_2D(position), this->get_color(),
                 this->get_first_move());
  display_vector_pos(possible_moves);
  return possible_moves;
}