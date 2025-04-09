#pragma once
#include "../Piece.hpp"

class Knight : public Piece {

public:
  explicit Knight(Color color) : Piece(color, Type::Knight, "knight.mp3") {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};