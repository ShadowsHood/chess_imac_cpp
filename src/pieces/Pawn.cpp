#include "./Pawn.hpp"
#include "./Board.hpp"
#include "utils.hpp"
#include "move.hpp"

std::vector<int> Pawn::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_pawn_moves(possible_moves, board, get_pos_2D(position), this->color,
                 this->first_move);
                 display_vector_pos(possible_moves);
  return possible_moves;
}