#pragma once
#include "../Piece.hpp"

class Rook : public Piece {

public:
  explicit Rook(Color color) : Piece(color, Type::Rook) {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};