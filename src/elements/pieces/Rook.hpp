#pragma once
#include "../Piece.hpp"

class Rook : public Piece {

public:
  explicit Rook(Color color) : Piece(color, Type::Rook, "rook.mp3") {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};