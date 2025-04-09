#pragma once
#include "../../Piece.hpp"

class Well : public Piece {
  private:
    int max_move {7};
    int direction {};

public:
  explicit Well(Color color) : Piece(color, Type::Well) {direction = color == Color::White ? 1 : -1;};

  std::vector<int> get_possible_moves(const Board &board, int position) override;
  void switch_direction();
};