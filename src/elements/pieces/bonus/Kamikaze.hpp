#pragma once
#include "../../Piece.hpp"

class Kamikaze : public Piece {
private:
  int time_before_explosion{};

public:
  explicit Kamikaze(Color color) : Piece(color, Type::Kamikaze, "") { init_time_before_explosion(); };

  std::vector<int> get_possible_moves(const Board &board,
                                      int position) override;
  
  void init_time_before_explosion();
  int get_time_before_explosion();
  void update_time_before_explosion(Board &board);
  void explode(Board &board);
};