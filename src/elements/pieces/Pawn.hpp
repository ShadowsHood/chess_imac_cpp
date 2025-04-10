#pragma once
#include "../Piece.hpp"

class Pawn : public Piece {

public:
  explicit Pawn(Color color) : Piece(color, Type::Pawn, "pawn.mp3") {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};