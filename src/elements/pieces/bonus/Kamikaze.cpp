#include "./Kamikaze.hpp"
#include "../../Board.hpp"
#include "../../../random/random.hpp"
#include "../../move.hpp" 
#include <algorithm>

std::vector<int> Kamikaze::get_possible_moves(const Board &board, int position) {
  std::vector<int> possible_moves;
  get_pawn_moves(possible_moves, board, get_pos_2D(position), this->get_color(),
                 this->get_first_move(), true);
  return possible_moves;
}

void Kamikaze::init_time_before_explosion() {
  this->time_before_explosion = Random::geometric_law_int();
}

int Kamikaze::get_time_before_explosion() {
  return this->time_before_explosion;
}

void Kamikaze::update_time_before_explosion(Board &board) {
  this->time_before_explosion--;
}

void Kamikaze::explode(Board &board) {
  int kamikaze_position = board.get_piece_position(this);
  for (int i = 0; i < 64; ++i) {
    if (distance_between_two_tiles(kamikaze_position, i) == 1) {
      board.kill_piece(i);
    }
  }
  board.kill_piece(kamikaze_position);
}