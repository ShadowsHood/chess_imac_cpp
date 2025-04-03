#pragma once
#include "../../Piece.hpp"

class Fool : public Piece {
private:
  int markovChain{0};

public:
  explicit Fool(Color color) : Piece(color, Type::Fool) {};

  bool canMove();

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};