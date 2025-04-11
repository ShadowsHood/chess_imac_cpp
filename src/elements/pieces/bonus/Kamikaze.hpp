#pragma once
#include "../../Piece.hpp"

class Kamikaze : public Piece {
private:
  int time_before_explosion{};

public:
  explicit Kamikaze(Color color) : Piece(color, Type::Kamikaze, "") {};

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;

  void init_time_before_explosion(Board &board);
  int get_time_before_explosion() const;
  void update_time_before_explosion();
  void explode(Board &board);
};