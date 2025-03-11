#include "./Bishop.hpp"
#include "../move.hpp"
#include "./utils.hpp"

std::vector<int> Bishop::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_up_right_moves(possible_moves, board, get_pos_2D(position),
                     this->get_color(), false);
  get_up_left_moves(possible_moves, board, get_pos_2D(position),
                    this->get_color(), false);
  get_down_right_moves(possible_moves, board, get_pos_2D(position),
                       this->get_color(), false);
  get_down_left_moves(possible_moves, board, get_pos_2D(position),
                      this->get_color(), false);
  display_vector_pos(possible_moves);
  return possible_moves;
}