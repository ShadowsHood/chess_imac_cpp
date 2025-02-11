#pragma once
#include "./pieces/Piece.hpp"
#include "./utils.hpp"
#include <array>
#include <iostream>
#include <vector>

class Board {

private:
  std::array<Piece *, 64> positions_board{};

private:
  void init_board();

public:
  inline Board() { this->init_board(); }
  ~Board() = default;

  void set_piece(Piece *piece, int position);

  bool is_in_board(int position);
  Piece *get_piece(std::pair<int, int> position) {
    return this->positions_board[get_pos_1D(position)] ? this->positions_board[get_pos_1D(position)] : nullptr;
  };
  bool is_empty(std::pair<int, int> position) {
    return this->positions_board[get_pos_1D(position)] == nullptr;
  };
  bool is_other_color(std::pair<int, int> position, Color color) {
    return this->positions_board[get_pos_1D(position)]->get_color() != color;
  };
};