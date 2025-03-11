#include "./King.hpp"
#include "../move.hpp"
#include "./utils.hpp"

std::vector<int> King::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;

  get_up_moves(possible_moves, board, get_pos_2D(position), this->get_color(),
               true);
  get_right_moves(possible_moves, board, get_pos_2D(position),
                  this->get_color(), true);
  get_down_moves(possible_moves, board, get_pos_2D(position), this->get_color(),
                 true);
  get_left_moves(possible_moves, board, get_pos_2D(position), this->get_color(),
                 true);
  get_up_right_moves(possible_moves, board, get_pos_2D(position),
                     this->get_color(), true);
  get_up_left_moves(possible_moves, board, get_pos_2D(position),
                    this->get_color(), true);
  get_down_right_moves(possible_moves, board, get_pos_2D(position),
                       this->get_color(), true);
  get_down_left_moves(possible_moves, board, get_pos_2D(position),
                      this->get_color(), true);
  display_vector_pos(possible_moves);
  return possible_moves;
}