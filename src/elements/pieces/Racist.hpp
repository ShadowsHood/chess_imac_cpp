#pragma once
#include "../Piece.hpp"

class Racist : public Piece {

public:
  explicit Racist(Color color) : Piece(color, Type::Racist) {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};