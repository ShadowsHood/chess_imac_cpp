#pragma once
#include "./Piece.hpp"
#include <array>
#include <iostream>

class Rook : public Piece {

public:
  explicit Rook(Color color) : Piece(color, Type::Rook) {
    this->set_char(color, Type::Rook);
  };
  ~Rook() override = default;

  std::vector<int>
  get_possible_moves(const Board & board,
                     int position) override;
};