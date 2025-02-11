#pragma once
#include "./Piece.hpp"
#include <array>
#include <iostream>

class Pawn : public Piece {

public:
  explicit Pawn(Color color) : Piece(color, Type::Pawn) {
    this->set_char(color, Type::Pawn);
  };
  ~Pawn() override = default;

  std::vector<int>
  get_possible_moves(const Board & board,
                     int position) override;
};