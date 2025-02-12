#pragma once
#include "./pieces/Piece.hpp"
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

  const std::array<Piece *, 64> &get_positions_board() const {
    return this->positions_board;
  }

  void set_piece(Piece *piece, int position);

  bool is_in_board(std::pair<int, int> position) const;

  Piece *get_piece(int position) {
    return this->positions_board[position] ? this->positions_board[position]
                                           : nullptr;
  };

  bool is_empty(int position) const {
    return this->positions_board[position] == nullptr;
  };

  bool is_other_color(int position, Color color) const {
    return this->positions_board[position]->get_color() != color;
  };
};