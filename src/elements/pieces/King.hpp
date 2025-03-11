#pragma once
#include "../Piece.hpp"

class King : public Piece {

public:
  explicit King(Color color) : Piece(color, Type::King) {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};