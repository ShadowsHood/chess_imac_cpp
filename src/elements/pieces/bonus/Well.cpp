#include "./Well.hpp"
#include "../../../random/random.hpp"
#include "../../Board.hpp"
#include <algorithm>
#include <cmath>

std::vector<int> Well::get_possible_moves(const Board & /*board*/,
                                          int /*position*/) {
  std::vector<int> possible_moves{};
  double x = Random::cauchy_law(1, 1);
  int value = static_cast<int>(std::round(x));
  value = std::max(value, 1);
  value = std::min(value, max_move);
  max_move -= value;
  possible_moves.push_back(value * direction);
  return possible_moves;
}

void Well::switch_direction() {
  direction = -direction;
  max_move = 7;
}