#pragma once
#include "../../Piece.hpp"

class Fool : public Piece {

public:
  explicit Fool(Color color) : Piece(color, Type::Fool) {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};