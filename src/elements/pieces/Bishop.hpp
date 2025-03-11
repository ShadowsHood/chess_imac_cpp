#pragma once
#include "../Piece.hpp"

class Bishop : public Piece {

public:
  explicit Bishop(Color color) : Piece(color, Type::Bishop) {};
  ~Bishop() override = default;

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
};