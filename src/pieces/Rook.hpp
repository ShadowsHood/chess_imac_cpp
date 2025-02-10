#pragma once
#include "./Piece.hpp"
#include <array>
#include <iostream>


class Rook : public Piece {

public:
  Rook(Color color) : Piece(color, Type::Rook) {
    this->set_char(color, Type::Rook);
  };
  virtual ~Rook() = default;

  std::vector<int>
  get_possible_moves(const std::array<Piece *, 64> &positions_board,
                     int position) override;
};