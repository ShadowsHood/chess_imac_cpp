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
  get_possible_moves(const Board & board,
                     int position) override;
};