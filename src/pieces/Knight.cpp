#include "./Knight.hpp"
#include "./Board.hpp"
#include <utils.hpp>

std::vector<int> Knight::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, -2, -1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, -2, 1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, 2, -1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, 2, 1);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, -1, 2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, 1, 2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, -1, -2);
  get_knight_tile_from_step(possible_moves, board, get_pos_2D(position),
                            this->color, 1, -2);
  return possible_moves;
}