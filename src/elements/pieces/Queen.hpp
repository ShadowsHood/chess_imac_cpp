#pragma once
#include "../Piece.hpp"

class Queen : public Piece {

public:
  explicit Queen(Color color) : Piece(color, Type::Queen, "queen.mp3") {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};