#include "./Knight.hpp"
#include "../move.hpp"
#include "utils.hpp"

std::vector<int> Knight::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), -2, -1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), -2, 1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), 2, -1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), 2, 1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), -1, 2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), 1, 2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), -1, -2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->get_color(), 1, -2);
  display_vector_pos(possible_moves);
  return possible_moves;
}