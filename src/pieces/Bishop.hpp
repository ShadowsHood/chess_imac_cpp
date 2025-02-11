#pragma once
#include "./Piece.hpp"
#include <array>
#include <iostream>

class Bishop : public Piece {

public:
  explicit Bishop(Color color) : Piece(color, Type::Bishop) {
    this->set_char(color, Type::Bishop);
  };
  ~Bishop() override = default;

  std::vector<int>
  get_possible_moves(const std::array<Piece *, 64> &positions_board,
                     int position) override;
};