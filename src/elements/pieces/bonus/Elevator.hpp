#pragma once
#include "../../Piece.hpp"

class Elevator : public Piece {
  private:
    int max_move {7};
    int direction {};

public:
  explicit Elevator(Color color) : Piece(color, Type::Elevator) {direction = color == Color::White ? 1 : -1;};

  std::vector<int> get_possible_moves(const Board &board, int position) override;
  void switch_direction();
};